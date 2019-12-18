#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ hierarchy_information; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  constellation; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct TYPE_4__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_2__ u; } ;
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; } ;
struct dib3000mc_state {int dummy; } ;

/* Variables and functions */
 void* FEC_2_3 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_set_channel_cfg (struct dib3000mc_state*,struct dvb_frontend_parameters*,int) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib3000mc_autosearch_start(struct dvb_frontend *demod, struct dvb_frontend_parameters *chan)
{
	struct dib3000mc_state *state = demod->demodulator_priv;
	u16 reg;
//	u32 val;
	struct dvb_frontend_parameters schan;

	schan = *chan;

	/* TODO what is that ? */

	/* a channel for autosearch */
	schan.u.ofdm.transmission_mode = TRANSMISSION_MODE_8K;
	schan.u.ofdm.guard_interval = GUARD_INTERVAL_1_32;
	schan.u.ofdm.constellation = QAM_64;
	schan.u.ofdm.code_rate_HP = FEC_2_3;
	schan.u.ofdm.code_rate_LP = FEC_2_3;
	schan.u.ofdm.hierarchy_information = 0;

	dib3000mc_set_channel_cfg(state, &schan, 11);

	reg = dib3000mc_read_word(state, 0);
	dib3000mc_write_word(state, 0, reg | (1 << 8));
	dib3000mc_read_word(state, 511);
	dib3000mc_write_word(state, 0, reg);

	return 0;
}