#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pvr2_hdw {TYPE_1__* hdw_desc; } ;
struct pvr2_dvb_props {scalar_t__ (* frontend_attach ) (struct pvr2_dvb_adapter*) ;int /*<<< orphan*/  (* tuner_attach ) (struct pvr2_dvb_adapter*) ;} ;
struct TYPE_12__ {struct pvr2_hdw* hdw; } ;
struct pvr2_dvb_adapter {TYPE_5__ channel; TYPE_4__* fe; int /*<<< orphan*/  dvb_adap; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* standby ) (TYPE_4__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  ts_bus_ctrl; TYPE_2__ analog_ops; } ;
struct TYPE_11__ {TYPE_3__ ops; } ;
struct TYPE_8__ {struct pvr2_dvb_props* dvb_props; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int PVR2_CVAL_INPUT_DTV ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_4__*) ; 
 scalar_t__ dvb_register_frontend (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int pvr2_channel_limit_inputs (TYPE_5__*,int) ; 
 int /*<<< orphan*/  pvr2_dvb_bus_ctrl ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

__attribute__((used)) static int pvr2_dvb_frontend_init(struct pvr2_dvb_adapter *adap)
{
	struct pvr2_hdw *hdw = adap->channel.hdw;
	const struct pvr2_dvb_props *dvb_props = hdw->hdw_desc->dvb_props;
	int ret = 0;

	if (dvb_props == NULL) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS, "fe_props not defined!");
		return -EINVAL;
	}

	ret = pvr2_channel_limit_inputs(
	    &adap->channel,
	    (1 << PVR2_CVAL_INPUT_DTV));
	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "failed to grab control of dtv input (code=%d)",
		    ret);
		return ret;
	}

	if (dvb_props->frontend_attach == NULL) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "frontend_attach not defined!");
		ret = -EINVAL;
		goto done;
	}

	if ((dvb_props->frontend_attach(adap) == 0) && (adap->fe)) {

		if (dvb_register_frontend(&adap->dvb_adap, adap->fe)) {
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "frontend registration failed!");
			dvb_frontend_detach(adap->fe);
			adap->fe = NULL;
			ret = -ENODEV;
			goto done;
		}

		if (dvb_props->tuner_attach)
			dvb_props->tuner_attach(adap);

		if (adap->fe->ops.analog_ops.standby)
			adap->fe->ops.analog_ops.standby(adap->fe);

		/* Ensure all frontends negotiate bus access */
		adap->fe->ops.ts_bus_ctrl = pvr2_dvb_bus_ctrl;

	} else {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "no frontend was attached!");
		ret = -ENODEV;
		return ret;
	}

 done:
	pvr2_channel_limit_inputs(&adap->channel, 0);
	return ret;
}