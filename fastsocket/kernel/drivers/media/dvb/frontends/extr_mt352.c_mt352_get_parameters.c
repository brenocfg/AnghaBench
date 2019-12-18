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
typedef  int u16 ;
struct mt352_state {int dummy; } ;
struct dvb_ofdm_parameters {int code_rate_HP; int code_rate_LP; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  constellation; } ;
struct TYPE_2__ {struct dvb_ofdm_parameters ofdm; } ;
struct dvb_frontend_parameters {int frequency; int /*<<< orphan*/  inversion; TYPE_1__ u; } ;
struct dvb_frontend {struct mt352_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_6_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_7_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
 int CHAN_START_0 ; 
 int CHAN_START_1 ; 
 int EINVAL ; 
#define  FEC_1_2 133 
#define  FEC_2_3 132 
#define  FEC_3_4 131 
#define  FEC_5_6 130 
#define  FEC_7_8 129 
#define  FEC_AUTO 128 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int IF_FREQUENCYx6 ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QAM_AUTO ; 
 int /*<<< orphan*/  QPSK ; 
 int STATUS_2 ; 
 int TPS_RECEIVED_0 ; 
 int TPS_RECEIVED_1 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int TRL_NOMINAL_RATE_1 ; 
 int mt352_read_register (struct mt352_state*,int) ; 

__attribute__((used)) static int mt352_get_parameters(struct dvb_frontend* fe,
				struct dvb_frontend_parameters *param)
{
	struct mt352_state* state = fe->demodulator_priv;
	u16 tps;
	u16 div;
	u8 trl;
	struct dvb_ofdm_parameters *op = &param->u.ofdm;
	static const u8 tps_fec_to_api[8] =
	{
		FEC_1_2,
		FEC_2_3,
		FEC_3_4,
		FEC_5_6,
		FEC_7_8,
		FEC_AUTO,
		FEC_AUTO,
		FEC_AUTO
	};

	if ( (mt352_read_register(state,0x00) & 0xC0) != 0xC0 )
		return -EINVAL;

	/* Use TPS_RECEIVED-registers, not the TPS_CURRENT-registers because
	 * the mt352 sometimes works with the wrong parameters
	 */
	tps = (mt352_read_register(state, TPS_RECEIVED_1) << 8) | mt352_read_register(state, TPS_RECEIVED_0);
	div = (mt352_read_register(state, CHAN_START_1) << 8) | mt352_read_register(state, CHAN_START_0);
	trl = mt352_read_register(state, TRL_NOMINAL_RATE_1);

	op->code_rate_HP = tps_fec_to_api[(tps >> 7) & 7];
	op->code_rate_LP = tps_fec_to_api[(tps >> 4) & 7];

	switch ( (tps >> 13) & 3)
	{
		case 0:
			op->constellation = QPSK;
			break;
		case 1:
			op->constellation = QAM_16;
			break;
		case 2:
			op->constellation = QAM_64;
			break;
		default:
			op->constellation = QAM_AUTO;
			break;
	}

	op->transmission_mode = (tps & 0x01) ? TRANSMISSION_MODE_8K : TRANSMISSION_MODE_2K;

	switch ( (tps >> 2) & 3)
	{
		case 0:
			op->guard_interval = GUARD_INTERVAL_1_32;
			break;
		case 1:
			op->guard_interval = GUARD_INTERVAL_1_16;
			break;
		case 2:
			op->guard_interval = GUARD_INTERVAL_1_8;
			break;
		case 3:
			op->guard_interval = GUARD_INTERVAL_1_4;
			break;
		default:
			op->guard_interval = GUARD_INTERVAL_AUTO;
			break;
	}

	switch ( (tps >> 10) & 7)
	{
		case 0:
			op->hierarchy_information = HIERARCHY_NONE;
			break;
		case 1:
			op->hierarchy_information = HIERARCHY_1;
			break;
		case 2:
			op->hierarchy_information = HIERARCHY_2;
			break;
		case 3:
			op->hierarchy_information = HIERARCHY_4;
			break;
		default:
			op->hierarchy_information = HIERARCHY_AUTO;
			break;
	}

	param->frequency = ( 500 * (div - IF_FREQUENCYx6) ) / 3 * 1000;

	if (trl == 0x72)
		op->bandwidth = BANDWIDTH_8_MHZ;
	else if (trl == 0x64)
		op->bandwidth = BANDWIDTH_7_MHZ;
	else
		op->bandwidth = BANDWIDTH_6_MHZ;


	if (mt352_read_register(state, STATUS_2) & 0x02)
		param->inversion = INVERSION_OFF;
	else
		param->inversion = INVERSION_ON;

	return 0;
}