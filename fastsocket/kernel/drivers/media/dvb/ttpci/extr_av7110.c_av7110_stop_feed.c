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
struct TYPE_7__ {int /*<<< orphan*/  sec; } ;
struct dvb_demux_feed {scalar_t__ type; int ts_type; size_t pes_type; TYPE_2__ feed; TYPE_5__* filter; struct dvb_demux* demux; } ;
struct TYPE_9__ {TYPE_3__* frontend; } ;
struct dvb_demux {int* pids; int filternum; TYPE_5__* filter; TYPE_4__ dmx; int /*<<< orphan*/ ** pesfilter; struct av7110* priv; } ;
struct av7110 {scalar_t__ full_ts; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {scalar_t__ state; TYPE_1__ filter; } ;
struct TYPE_8__ {scalar_t__ source; } ;

/* Variables and functions */
 scalar_t__ DMX_MEMORY_FE ; 
 scalar_t__ DMX_STATE_GO ; 
 scalar_t__ DMX_STATE_READY ; 
 size_t DMX_TS_PES_OTHER ; 
 scalar_t__ DMX_TYPE_SEC ; 
 scalar_t__ DMX_TYPE_TS ; 
 int EINVAL ; 
 int StopHWFilter (TYPE_5__*) ; 
 int TS_DECODER ; 
 int TS_PACKET ; 
 int /*<<< orphan*/  budget_stop_feed (struct dvb_demux_feed*) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int dvb_feed_stop_pid (struct dvb_demux_feed*) ; 

__attribute__((used)) static int av7110_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct av7110 *av7110 = demux->priv;
	int i, rc, ret = 0;
	dprintk(4, "%p\n", av7110);

	if (feed->type == DMX_TYPE_TS) {
		if (feed->ts_type & TS_DECODER) {
			if (feed->pes_type >= DMX_TS_PES_OTHER ||
			    !demux->pesfilter[feed->pes_type])
				return -EINVAL;
			demux->pids[feed->pes_type] |= 0x8000;
			demux->pesfilter[feed->pes_type] = NULL;
		}
		if (feed->ts_type & TS_DECODER &&
		    feed->pes_type < DMX_TS_PES_OTHER) {
			ret = dvb_feed_stop_pid(feed);
		} else
			if ((feed->ts_type & TS_PACKET) &&
			    (demux->dmx.frontend->source != DMX_MEMORY_FE))
				ret = StopHWFilter(feed->filter);
	}

	if (av7110->full_ts) {
		budget_stop_feed(feed);
		return ret;
	}

	if (feed->type == DMX_TYPE_SEC) {
		for (i = 0; i<demux->filternum; i++) {
			if (demux->filter[i].state == DMX_STATE_GO &&
			    demux->filter[i].filter.parent == &feed->feed.sec) {
				demux->filter[i].state = DMX_STATE_READY;
				if (demux->dmx.frontend->source != DMX_MEMORY_FE) {
					rc = StopHWFilter(&demux->filter[i]);
					if (!ret)
						ret = rc;
					/* keep going, stop as many filters as possible */
				}
			}
		}
	}

	return ret;
}