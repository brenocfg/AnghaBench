#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct lgs8gl5_state {int dummy; } ;
struct dvb_ofdm_parameters {int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  constellation; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; } ;
struct TYPE_2__ {struct dvb_ofdm_parameters ofdm; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  inversion; TYPE_1__ u; } ;
struct dvb_frontend {struct lgs8gl5_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  REG_INVERSION ; 
 int REG_INVERSION_ON ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int lgs8gl5_read_reg (struct lgs8gl5_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lgs8gl5_get_frontend(struct dvb_frontend *fe,
		struct dvb_frontend_parameters *p)
{
	struct lgs8gl5_state *state = fe->demodulator_priv;
	u8 inv = lgs8gl5_read_reg(state, REG_INVERSION);
	struct dvb_ofdm_parameters *o = &p->u.ofdm;

	p->inversion = (inv & REG_INVERSION_ON) ? INVERSION_ON : INVERSION_OFF;

	o->code_rate_HP = FEC_1_2;
	o->code_rate_LP = FEC_7_8;
	o->guard_interval = GUARD_INTERVAL_1_32;
	o->transmission_mode = TRANSMISSION_MODE_2K;
	o->constellation = QAM_64;
	o->hierarchy_information = HIERARCHY_NONE;
	o->bandwidth = BANDWIDTH_8_MHZ;

	return 0;
}