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
struct dmx_section_feed {int /*<<< orphan*/  release_filter; int /*<<< orphan*/  stop_filtering; int /*<<< orphan*/  start_filtering; int /*<<< orphan*/  allocate_filter; int /*<<< orphan*/  set; int /*<<< orphan*/ * priv; struct dmx_demux* parent; scalar_t__ is_filtering; scalar_t__ tsfeedp; scalar_t__ seclen; scalar_t__ secbufp; int /*<<< orphan*/  secbuf_base; int /*<<< orphan*/  secbuf; } ;
struct TYPE_4__ {struct dmx_section_feed sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  sec; } ;
struct dvb_demux_feed {int pid; TYPE_2__ feed; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * filter; struct dvb_demux* demux; TYPE_1__ cb; int /*<<< orphan*/  type; } ;
struct dvb_demux {int /*<<< orphan*/  mutex; } ;
struct dmx_demux {int dummy; } ;
typedef  int /*<<< orphan*/  dmx_section_cb ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_TYPE_SEC ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dmx_section_feed_allocate_filter ; 
 int /*<<< orphan*/  dmx_section_feed_release_filter ; 
 int /*<<< orphan*/  dmx_section_feed_set ; 
 int /*<<< orphan*/  dmx_section_feed_start_filtering ; 
 int /*<<< orphan*/  dmx_section_feed_stop_filtering ; 
 struct dvb_demux_feed* dvb_dmx_feed_alloc (struct dvb_demux*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvbdmx_allocate_section_feed(struct dmx_demux *demux,
					struct dmx_section_feed **feed,
					dmx_section_cb callback)
{
	struct dvb_demux *dvbdmx = (struct dvb_demux *)demux;
	struct dvb_demux_feed *dvbdmxfeed;

	if (mutex_lock_interruptible(&dvbdmx->mutex))
		return -ERESTARTSYS;

	if (!(dvbdmxfeed = dvb_dmx_feed_alloc(dvbdmx))) {
		mutex_unlock(&dvbdmx->mutex);
		return -EBUSY;
	}

	dvbdmxfeed->type = DMX_TYPE_SEC;
	dvbdmxfeed->cb.sec = callback;
	dvbdmxfeed->demux = dvbdmx;
	dvbdmxfeed->pid = 0xffff;
	dvbdmxfeed->feed.sec.secbuf = dvbdmxfeed->feed.sec.secbuf_base;
	dvbdmxfeed->feed.sec.secbufp = dvbdmxfeed->feed.sec.seclen = 0;
	dvbdmxfeed->feed.sec.tsfeedp = 0;
	dvbdmxfeed->filter = NULL;
	dvbdmxfeed->buffer = NULL;

	(*feed) = &dvbdmxfeed->feed.sec;
	(*feed)->is_filtering = 0;
	(*feed)->parent = demux;
	(*feed)->priv = NULL;

	(*feed)->set = dmx_section_feed_set;
	(*feed)->allocate_filter = dmx_section_feed_allocate_filter;
	(*feed)->start_filtering = dmx_section_feed_start_filtering;
	(*feed)->stop_filtering = dmx_section_feed_stop_filtering;
	(*feed)->release_filter = dmx_section_feed_release_filter;

	mutex_unlock(&dvbdmx->mutex);
	return 0;
}