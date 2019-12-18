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
struct dvb_demux_feed {scalar_t__ state; int pid; int ts_type; size_t pes_type; TYPE_1__* filter; int /*<<< orphan*/ * buffer; } ;
struct dvb_demux {int /*<<< orphan*/  mutex; int /*<<< orphan*/ ** pesfilter; } ;
struct dmx_ts_feed {int dummy; } ;
struct dmx_demux {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DMX_STATE_FREE ; 
 size_t DMX_TS_PES_OTHER ; 
 int EINVAL ; 
 int TS_DECODER ; 
 int /*<<< orphan*/  dvb_demux_feed_del (struct dvb_demux_feed*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvbdmx_release_ts_feed(struct dmx_demux *dmx,
				  struct dmx_ts_feed *ts_feed)
{
	struct dvb_demux *demux = (struct dvb_demux *)dmx;
	struct dvb_demux_feed *feed = (struct dvb_demux_feed *)ts_feed;

	mutex_lock(&demux->mutex);

	if (feed->state == DMX_STATE_FREE) {
		mutex_unlock(&demux->mutex);
		return -EINVAL;
	}
#ifndef NOBUFS
	vfree(feed->buffer);
	feed->buffer = NULL;
#endif

	feed->state = DMX_STATE_FREE;
	feed->filter->state = DMX_STATE_FREE;

	dvb_demux_feed_del(feed);

	feed->pid = 0xffff;

	if (feed->ts_type & TS_DECODER && feed->pes_type < DMX_TS_PES_OTHER)
		demux->pesfilter[feed->pes_type] = NULL;

	mutex_unlock(&demux->mutex);
	return 0;
}