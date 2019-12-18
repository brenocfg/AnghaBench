#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dvb_adapter {int dummy; } ;
struct dmxdev_filter {int dummy; } ;
struct dmxdev {int filternum; int /*<<< orphan*/  dvr_buffer; int /*<<< orphan*/  dvr_dvbdev; int /*<<< orphan*/  dvbdev; TYPE_2__* filter; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; TYPE_3__* demux; } ;
struct TYPE_7__ {scalar_t__ (* open ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_1__ buffer; struct dmxdev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMXDEV_STATE_FREE ; 
 int /*<<< orphan*/  DVB_DEVICE_DEMUX ; 
 int /*<<< orphan*/  DVB_DEVICE_DVR ; 
 int ENOMEM ; 
 int EUSERS ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_state_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_register_device (struct dvb_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dmxdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_ringbuffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dvbdev_demux ; 
 int /*<<< orphan*/  dvbdev_dvr ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 TYPE_2__* vmalloc (int) ; 

int dvb_dmxdev_init(struct dmxdev *dmxdev, struct dvb_adapter *dvb_adapter)
{
	int i;

	if (dmxdev->demux->open(dmxdev->demux) < 0)
		return -EUSERS;

	dmxdev->filter = vmalloc(dmxdev->filternum * sizeof(struct dmxdev_filter));
	if (!dmxdev->filter)
		return -ENOMEM;

	mutex_init(&dmxdev->mutex);
	spin_lock_init(&dmxdev->lock);
	for (i = 0; i < dmxdev->filternum; i++) {
		dmxdev->filter[i].dev = dmxdev;
		dmxdev->filter[i].buffer.data = NULL;
		dvb_dmxdev_filter_state_set(&dmxdev->filter[i],
					    DMXDEV_STATE_FREE);
	}

	dvb_register_device(dvb_adapter, &dmxdev->dvbdev, &dvbdev_demux, dmxdev,
			    DVB_DEVICE_DEMUX);
	dvb_register_device(dvb_adapter, &dmxdev->dvr_dvbdev, &dvbdev_dvr,
			    dmxdev, DVB_DEVICE_DVR);

	dvb_ringbuffer_init(&dmxdev->dvr_buffer, NULL, 8192);

	return 0;
}