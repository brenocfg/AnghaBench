#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mxl5007t_state {int bandwidth; int /*<<< orphan*/  lock; int /*<<< orphan*/  frequency; } ;
struct TYPE_8__ {int bandwidth; } ;
struct TYPE_6__ {int modulation; } ;
struct TYPE_9__ {TYPE_3__ ofdm; TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {TYPE_4__ u; int /*<<< orphan*/  frequency; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_2__ info; } ;
struct dvb_frontend {TYPE_5__ ops; struct mxl5007t_state* tuner_priv; } ;
typedef  enum mxl5007t_mode { ____Placeholder_mxl5007t_mode } mxl5007t_mode ;
typedef  enum mxl5007t_bw_mhz { ____Placeholder_mxl5007t_bw_mhz } mxl5007t_bw_mhz ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 134 
#define  BANDWIDTH_7_MHZ 133 
#define  BANDWIDTH_8_MHZ 132 
 int EINVAL ; 
 scalar_t__ FE_ATSC ; 
 scalar_t__ FE_OFDM ; 
 int MxL_BW_6MHz ; 
 int MxL_BW_7MHz ; 
 int MxL_BW_8MHz ; 
 int MxL_MODE_ATSC ; 
 int MxL_MODE_CABLE ; 
 int MxL_MODE_DVBT ; 
#define  QAM_256 131 
#define  QAM_64 130 
#define  VSB_16 129 
#define  VSB_8 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mxl5007t_tuner_init (struct mxl5007t_state*,int) ; 
 int mxl5007t_tuner_rf_tune (struct mxl5007t_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxl_err (char*) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mxl5007t_set_params(struct dvb_frontend *fe,
			       struct dvb_frontend_parameters *params)
{
	struct mxl5007t_state *state = fe->tuner_priv;
	enum mxl5007t_bw_mhz bw;
	enum mxl5007t_mode mode;
	int ret;
	u32 freq = params->frequency;

	if (fe->ops.info.type == FE_ATSC) {
		switch (params->u.vsb.modulation) {
		case VSB_8:
		case VSB_16:
			mode = MxL_MODE_ATSC;
			break;
		case QAM_64:
		case QAM_256:
			mode = MxL_MODE_CABLE;
			break;
		default:
			mxl_err("modulation not set!");
			return -EINVAL;
		}
		bw = MxL_BW_6MHz;
	} else if (fe->ops.info.type == FE_OFDM) {
		switch (params->u.ofdm.bandwidth) {
		case BANDWIDTH_6_MHZ:
			bw = MxL_BW_6MHz;
			break;
		case BANDWIDTH_7_MHZ:
			bw = MxL_BW_7MHz;
			break;
		case BANDWIDTH_8_MHZ:
			bw = MxL_BW_8MHz;
			break;
		default:
			mxl_err("bandwidth not set!");
			return -EINVAL;
		}
		mode = MxL_MODE_DVBT;
	} else {
		mxl_err("modulation type not supported!");
		return -EINVAL;
	}

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	mutex_lock(&state->lock);

	ret = mxl5007t_tuner_init(state, mode);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl5007t_tuner_rf_tune(state, freq, bw);
	if (mxl_fail(ret))
		goto fail;

	state->frequency = freq;
	state->bandwidth = (fe->ops.info.type == FE_OFDM) ?
		params->u.ofdm.bandwidth : 0;
fail:
	mutex_unlock(&state->lock);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return ret;
}