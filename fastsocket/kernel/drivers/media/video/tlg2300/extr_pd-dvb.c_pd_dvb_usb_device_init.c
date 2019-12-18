#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ops; struct poseidon* demodulator_priv; } ;
struct TYPE_7__ {int filternum; scalar_t__ capabilities; TYPE_1__* demux; } ;
struct TYPE_5__ {int capabilities; } ;
struct dvb_demux {int feednum; int filternum; TYPE_1__ dmx; int /*<<< orphan*/ * write_to_decoder; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct pd_dvb_adapter* priv; } ;
struct pd_dvb_adapter {int ep_addr; int /*<<< orphan*/  dvb_adap; TYPE_2__ dvb_fe; TYPE_4__ dmxdev; struct dvb_demux demux; struct poseidon* pd_device; int /*<<< orphan*/  active_feed; int /*<<< orphan*/  users; } ;
struct poseidon {struct pd_dvb_adapter dvb_data; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dvb_dmx_init (struct dvb_demux*) ; 
 int dvb_dmxdev_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int dvb_register_adapter (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dvb_register_frontend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pd_start_feed ; 
 int /*<<< orphan*/  pd_stop_feed ; 
 int /*<<< orphan*/  poseidon_frontend_ops ; 

int pd_dvb_usb_device_init(struct poseidon *pd)
{
	struct pd_dvb_adapter *pd_dvb = &pd->dvb_data;
	struct dvb_demux *dvbdemux;
	int ret = 0;

	pd_dvb->ep_addr = 0x82;
	atomic_set(&pd_dvb->users, 0);
	atomic_set(&pd_dvb->active_feed, 0);
	pd_dvb->pd_device = pd;

	ret = dvb_register_adapter(&pd_dvb->dvb_adap,
				"Poseidon dvbt adapter",
				THIS_MODULE,
				NULL /* for hibernation correctly*/,
				adapter_nr);
	if (ret < 0)
		goto error1;

	/* register frontend */
	pd_dvb->dvb_fe.demodulator_priv = pd;
	memcpy(&pd_dvb->dvb_fe.ops, &poseidon_frontend_ops,
			sizeof(struct dvb_frontend_ops));
	ret = dvb_register_frontend(&pd_dvb->dvb_adap, &pd_dvb->dvb_fe);
	if (ret < 0)
		goto error2;

	/* register demux device */
	dvbdemux = &pd_dvb->demux;
	dvbdemux->dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	dvbdemux->priv = pd_dvb;
	dvbdemux->feednum = dvbdemux->filternum = 64;
	dvbdemux->start_feed = pd_start_feed;
	dvbdemux->stop_feed = pd_stop_feed;
	dvbdemux->write_to_decoder = NULL;

	ret = dvb_dmx_init(dvbdemux);
	if (ret < 0)
		goto error3;

	pd_dvb->dmxdev.filternum = pd_dvb->demux.filternum;
	pd_dvb->dmxdev.demux = &pd_dvb->demux.dmx;
	pd_dvb->dmxdev.capabilities = 0;

	ret = dvb_dmxdev_init(&pd_dvb->dmxdev, &pd_dvb->dvb_adap);
	if (ret < 0)
		goto error3;
	return 0;

error3:
	dvb_unregister_frontend(&pd_dvb->dvb_fe);
error2:
	dvb_unregister_adapter(&pd_dvb->dvb_adap);
error1:
	return ret;
}