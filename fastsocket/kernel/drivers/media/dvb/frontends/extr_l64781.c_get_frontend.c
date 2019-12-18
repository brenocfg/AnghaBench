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
struct l64781_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  constellation; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; } ;
struct TYPE_4__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; int /*<<< orphan*/  inversion; TYPE_2__ u; } ;
struct dvb_frontend {struct l64781_state* demodulator_priv; } ;

/* Variables and functions */
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_5_6 ; 
 void* FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int l64781_readreg (struct l64781_state*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int get_frontend(struct dvb_frontend* fe, struct dvb_frontend_parameters* param)
{
	struct l64781_state* state = fe->demodulator_priv;
	int tmp;


	tmp = l64781_readreg(state, 0x04);
	switch(tmp & 3) {
	case 0:
		param->u.ofdm.guard_interval = GUARD_INTERVAL_1_32;
		break;
	case 1:
		param->u.ofdm.guard_interval = GUARD_INTERVAL_1_16;
		break;
	case 2:
		param->u.ofdm.guard_interval = GUARD_INTERVAL_1_8;
		break;
	case 3:
		param->u.ofdm.guard_interval = GUARD_INTERVAL_1_4;
		break;
	}
	switch((tmp >> 2) & 3) {
	case 0:
		param->u.ofdm.transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		param->u.ofdm.transmission_mode = TRANSMISSION_MODE_8K;
		break;
	default:
		printk("Unexpected value for transmission_mode\n");
	}



	tmp = l64781_readreg(state, 0x05);
	switch(tmp & 7) {
	case 0:
		param->u.ofdm.code_rate_HP = FEC_1_2;
		break;
	case 1:
		param->u.ofdm.code_rate_HP = FEC_2_3;
		break;
	case 2:
		param->u.ofdm.code_rate_HP = FEC_3_4;
		break;
	case 3:
		param->u.ofdm.code_rate_HP = FEC_5_6;
		break;
	case 4:
		param->u.ofdm.code_rate_HP = FEC_7_8;
		break;
	default:
		printk("Unexpected value for code_rate_HP\n");
	}
	switch((tmp >> 3) & 7) {
	case 0:
		param->u.ofdm.code_rate_LP = FEC_1_2;
		break;
	case 1:
		param->u.ofdm.code_rate_LP = FEC_2_3;
		break;
	case 2:
		param->u.ofdm.code_rate_LP = FEC_3_4;
		break;
	case 3:
		param->u.ofdm.code_rate_LP = FEC_5_6;
		break;
	case 4:
		param->u.ofdm.code_rate_LP = FEC_7_8;
		break;
	default:
		printk("Unexpected value for code_rate_LP\n");
	}


	tmp = l64781_readreg(state, 0x06);
	switch(tmp & 3) {
	case 0:
		param->u.ofdm.constellation = QPSK;
		break;
	case 1:
		param->u.ofdm.constellation = QAM_16;
		break;
	case 2:
		param->u.ofdm.constellation = QAM_64;
		break;
	default:
		printk("Unexpected value for constellation\n");
	}
	switch((tmp >> 2) & 7) {
	case 0:
		param->u.ofdm.hierarchy_information = HIERARCHY_NONE;
		break;
	case 1:
		param->u.ofdm.hierarchy_information = HIERARCHY_1;
		break;
	case 2:
		param->u.ofdm.hierarchy_information = HIERARCHY_2;
		break;
	case 3:
		param->u.ofdm.hierarchy_information = HIERARCHY_4;
		break;
	default:
		printk("Unexpected value for hierarchy\n");
	}


	tmp = l64781_readreg (state, 0x1d);
	param->inversion = (tmp & 0x80) ? INVERSION_ON : INVERSION_OFF;

	tmp = (int) (l64781_readreg (state, 0x08) |
		     (l64781_readreg (state, 0x09) << 8) |
		     (l64781_readreg (state, 0x0a) << 16));
	param->frequency += tmp;

	return 0;
}