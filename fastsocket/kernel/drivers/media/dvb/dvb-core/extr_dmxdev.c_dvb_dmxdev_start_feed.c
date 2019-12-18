#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  member_0; } ;
struct dmx_pes_filter_params {scalar_t__ output; scalar_t__ pes_type; } ;
struct TYPE_5__ {struct dmx_pes_filter_params pes; } ;
struct dmxdev_filter {TYPE_1__ params; } ;
struct dmxdev_feed {int /*<<< orphan*/  pid; struct dmx_ts_feed* ts; } ;
struct dmxdev {TYPE_2__* demux; } ;
struct dmx_ts_feed {int (* set ) (struct dmx_ts_feed*,int /*<<< orphan*/ ,int,scalar_t__,int,struct timespec) ;int (* start_filtering ) (struct dmx_ts_feed*) ;struct dmxdev_filter* priv; } ;
typedef  scalar_t__ dmx_pes_type_t ;
typedef  scalar_t__ dmx_output_t ;
struct TYPE_6__ {int (* allocate_ts_feed ) (TYPE_2__*,struct dmx_ts_feed**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* release_ts_feed ) (TYPE_2__*,struct dmx_ts_feed*) ;} ;

/* Variables and functions */
 scalar_t__ DMX_OUT_TAP ; 
 scalar_t__ DMX_OUT_TSDEMUX_TAP ; 
 scalar_t__ DMX_OUT_TS_TAP ; 
 scalar_t__ DMX_PES_OTHER ; 
 int TS_DECODER ; 
 int TS_DEMUX ; 
 int TS_PACKET ; 
 int TS_PAYLOAD_ONLY ; 
 int /*<<< orphan*/  dvb_dmxdev_ts_callback ; 
 int stub1 (TYPE_2__*,struct dmx_ts_feed**,int /*<<< orphan*/ ) ; 
 int stub2 (struct dmx_ts_feed*,int /*<<< orphan*/ ,int,scalar_t__,int,struct timespec) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,struct dmx_ts_feed*) ; 
 int stub4 (struct dmx_ts_feed*) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,struct dmx_ts_feed*) ; 

__attribute__((used)) static int dvb_dmxdev_start_feed(struct dmxdev *dmxdev,
				 struct dmxdev_filter *filter,
				 struct dmxdev_feed *feed)
{
	struct timespec timeout = { 0 };
	struct dmx_pes_filter_params *para = &filter->params.pes;
	dmx_output_t otype;
	int ret;
	int ts_type;
	dmx_pes_type_t ts_pes;
	struct dmx_ts_feed *tsfeed;

	feed->ts = NULL;
	otype = para->output;

	ts_pes = para->pes_type;

	if (ts_pes < DMX_PES_OTHER)
		ts_type = TS_DECODER;
	else
		ts_type = 0;

	if (otype == DMX_OUT_TS_TAP)
		ts_type |= TS_PACKET;
	else if (otype == DMX_OUT_TSDEMUX_TAP)
		ts_type |= TS_PACKET | TS_DEMUX;
	else if (otype == DMX_OUT_TAP)
		ts_type |= TS_PACKET | TS_DEMUX | TS_PAYLOAD_ONLY;

	ret = dmxdev->demux->allocate_ts_feed(dmxdev->demux, &feed->ts,
					      dvb_dmxdev_ts_callback);
	if (ret < 0)
		return ret;

	tsfeed = feed->ts;
	tsfeed->priv = filter;

	ret = tsfeed->set(tsfeed, feed->pid, ts_type, ts_pes, 32768, timeout);
	if (ret < 0) {
		dmxdev->demux->release_ts_feed(dmxdev->demux, tsfeed);
		return ret;
	}

	ret = tsfeed->start_filtering(tsfeed);
	if (ret < 0) {
		dmxdev->demux->release_ts_feed(dmxdev->demux, tsfeed);
		return ret;
	}

	return 0;
}