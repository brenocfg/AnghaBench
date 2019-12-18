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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  bandwidth; scalar_t__ hierarchy_information; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  constellation; } ;
struct TYPE_4__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_2__ u; } ;
struct dvb_frontend {struct dib7000m_state* demodulator_priv; } ;
struct dib7000m_state {int internal_clk; int revision; } ;

/* Variables and functions */
 int BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int /*<<< orphan*/  dib7000m_set_channel (struct dib7000m_state*,struct dvb_frontend_parameters*,int) ; 
 int dib7000m_write_word (struct dib7000m_state*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib7000m_autosearch_start(struct dvb_frontend *demod, struct dvb_frontend_parameters *ch)
{
	struct dib7000m_state *state = demod->demodulator_priv;
	struct dvb_frontend_parameters schan;
	int ret = 0;
	u32 value, factor;

	schan = *ch;

	schan.u.ofdm.constellation = QAM_64;
	schan.u.ofdm.guard_interval        = GUARD_INTERVAL_1_32;
	schan.u.ofdm.transmission_mode         = TRANSMISSION_MODE_8K;
	schan.u.ofdm.code_rate_HP = FEC_2_3;
	schan.u.ofdm.code_rate_LP = FEC_3_4;
	schan.u.ofdm.hierarchy_information         = 0;

	dib7000m_set_channel(state, &schan, 7);

	factor = BANDWIDTH_TO_KHZ(ch->u.ofdm.bandwidth);
	if (factor >= 5000)
		factor = 1;
	else
		factor = 6;

	// always use the setting for 8MHz here lock_time for 7,6 MHz are longer
	value = 30 * state->internal_clk * factor;
	ret |= dib7000m_write_word(state, 6,  (u16) ((value >> 16) & 0xffff)); // lock0 wait time
	ret |= dib7000m_write_word(state, 7,  (u16)  (value        & 0xffff)); // lock0 wait time
	value = 100 * state->internal_clk * factor;
	ret |= dib7000m_write_word(state, 8,  (u16) ((value >> 16) & 0xffff)); // lock1 wait time
	ret |= dib7000m_write_word(state, 9,  (u16)  (value        & 0xffff)); // lock1 wait time
	value = 500 * state->internal_clk * factor;
	ret |= dib7000m_write_word(state, 10, (u16) ((value >> 16) & 0xffff)); // lock2 wait time
	ret |= dib7000m_write_word(state, 11, (u16)  (value        & 0xffff)); // lock2 wait time

	// start search
	value = dib7000m_read_word(state, 0);
	ret |= dib7000m_write_word(state, 0, (u16) (value | (1 << 9)));

	/* clear n_irq_pending */
	if (state->revision == 0x4000)
		dib7000m_write_word(state, 1793, 0);
	else
		dib7000m_read_word(state, 537);

	ret |= dib7000m_write_word(state, 0, (u16) value);

	return ret;
}