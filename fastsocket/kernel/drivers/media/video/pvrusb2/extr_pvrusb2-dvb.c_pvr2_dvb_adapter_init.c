#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {struct pvr2_dvb_adapter* priv; } ;
struct TYPE_17__ {int capabilities; } ;
struct TYPE_12__ {int filternum; int feednum; TYPE_7__ dmx; int /*<<< orphan*/ * write_to_decoder; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct pvr2_dvb_adapter* priv; } ;
struct TYPE_18__ {int filternum; scalar_t__ capabilities; TYPE_7__* demux; } ;
struct TYPE_15__ {TYPE_2__* hdw; } ;
struct pvr2_dvb_adapter {TYPE_4__ dvb_adap; TYPE_10__ demux; int /*<<< orphan*/  dvb_net; TYPE_8__ dmxdev; TYPE_3__ channel; } ;
struct TYPE_14__ {TYPE_1__* usb_dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMX_MEMORY_BASED_FILTERING ; 
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int dvb_dmx_init (TYPE_10__*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_10__*) ; 
 int dvb_dmxdev_init (TYPE_8__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dvb_net_init (TYPE_4__*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int dvb_register_adapter (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  pvr2_dvb_start_feed ; 
 int /*<<< orphan*/  pvr2_dvb_stop_feed ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int pvr2_dvb_adapter_init(struct pvr2_dvb_adapter *adap)
{
	int ret;

	ret = dvb_register_adapter(&adap->dvb_adap, "pvrusb2-dvb",
				   THIS_MODULE/*&hdw->usb_dev->owner*/,
				   &adap->channel.hdw->usb_dev->dev,
				   adapter_nr);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "dvb_register_adapter failed: error %d", ret);
		goto err;
	}
	adap->dvb_adap.priv = adap;

	adap->demux.dmx.capabilities = DMX_TS_FILTERING |
				       DMX_SECTION_FILTERING |
				       DMX_MEMORY_BASED_FILTERING;
	adap->demux.priv             = adap;
	adap->demux.filternum        = 256;
	adap->demux.feednum          = 256;
	adap->demux.start_feed       = pvr2_dvb_start_feed;
	adap->demux.stop_feed        = pvr2_dvb_stop_feed;
	adap->demux.write_to_decoder = NULL;

	ret = dvb_dmx_init(&adap->demux);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "dvb_dmx_init failed: error %d", ret);
		goto err_dmx;
	}

	adap->dmxdev.filternum       = adap->demux.filternum;
	adap->dmxdev.demux           = &adap->demux.dmx;
	adap->dmxdev.capabilities    = 0;

	ret = dvb_dmxdev_init(&adap->dmxdev, &adap->dvb_adap);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "dvb_dmxdev_init failed: error %d", ret);
		goto err_dmx_dev;
	}

	dvb_net_init(&adap->dvb_adap, &adap->dvb_net, &adap->demux.dmx);

	return 0;

err_dmx_dev:
	dvb_dmx_release(&adap->demux);
err_dmx:
	dvb_unregister_adapter(&adap->dvb_adap);
err:
	return ret;
}