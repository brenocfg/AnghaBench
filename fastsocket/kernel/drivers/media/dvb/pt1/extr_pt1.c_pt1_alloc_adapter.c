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
typedef  int /*<<< orphan*/  u8 ;
struct dmxdev {int filternum; scalar_t__ capabilities; TYPE_2__* demux; } ;
struct TYPE_4__ {int capabilities; } ;
struct dvb_demux {int feednum; int filternum; TYPE_2__ dmx; int /*<<< orphan*/ * write_to_decoder; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; struct pt1_adapter* priv; } ;
struct dvb_adapter {struct pt1_adapter* priv; } ;
struct pt1_adapter {int sleep; int /*<<< orphan*/  net; struct dmxdev dmxdev; struct dvb_demux demux; struct dvb_adapter adap; scalar_t__ packet_count; scalar_t__ upacket_count; void* buf; int /*<<< orphan*/  voltage; struct pt1* pt1; } ;
struct pt1 {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMX_SECTION_FILTERING ; 
 int DMX_TS_FILTERING ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 struct pt1_adapter* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEC_VOLTAGE_OFF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adapter_nr ; 
 int dvb_dmx_init (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int dvb_dmxdev_init (struct dmxdev*,struct dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_net_init (struct dvb_adapter*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int dvb_register_adapter (struct dvb_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (struct dvb_adapter*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct pt1_adapter*) ; 
 struct pt1_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_start_feed ; 
 int /*<<< orphan*/  pt1_stop_feed ; 

__attribute__((used)) static struct pt1_adapter *
pt1_alloc_adapter(struct pt1 *pt1)
{
	struct pt1_adapter *adap;
	void *buf;
	struct dvb_adapter *dvb_adap;
	struct dvb_demux *demux;
	struct dmxdev *dmxdev;
	int ret;

	adap = kzalloc(sizeof(struct pt1_adapter), GFP_KERNEL);
	if (!adap) {
		ret = -ENOMEM;
		goto err;
	}

	adap->pt1 = pt1;

	adap->voltage = SEC_VOLTAGE_OFF;
	adap->sleep = 1;

	buf = (u8 *)__get_free_page(GFP_KERNEL);
	if (!buf) {
		ret = -ENOMEM;
		goto err_kfree;
	}

	adap->buf = buf;
	adap->upacket_count = 0;
	adap->packet_count = 0;

	dvb_adap = &adap->adap;
	dvb_adap->priv = adap;
	ret = dvb_register_adapter(dvb_adap, DRIVER_NAME, THIS_MODULE,
				   &pt1->pdev->dev, adapter_nr);
	if (ret < 0)
		goto err_free_page;

	demux = &adap->demux;
	demux->dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;
	demux->priv = adap;
	demux->feednum = 256;
	demux->filternum = 256;
	demux->start_feed = pt1_start_feed;
	demux->stop_feed = pt1_stop_feed;
	demux->write_to_decoder = NULL;
	ret = dvb_dmx_init(demux);
	if (ret < 0)
		goto err_unregister_adapter;

	dmxdev = &adap->dmxdev;
	dmxdev->filternum = 256;
	dmxdev->demux = &demux->dmx;
	dmxdev->capabilities = 0;
	ret = dvb_dmxdev_init(dmxdev, dvb_adap);
	if (ret < 0)
		goto err_dmx_release;

	dvb_net_init(dvb_adap, &adap->net, &demux->dmx);

	return adap;

err_dmx_release:
	dvb_dmx_release(demux);
err_unregister_adapter:
	dvb_unregister_adapter(dvb_adap);
err_free_page:
	free_page((unsigned long)buf);
err_kfree:
	kfree(adap);
err:
	return ERR_PTR(ret);
}