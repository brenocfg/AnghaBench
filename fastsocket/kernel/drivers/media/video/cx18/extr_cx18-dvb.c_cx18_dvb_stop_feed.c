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
struct dvb_demux_feed {int /*<<< orphan*/  index; int /*<<< orphan*/  pid; struct dvb_demux* demux; } ;
struct dvb_demux {scalar_t__ priv; } ;
struct cx18_stream {TYPE_1__* dvb; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; } ;
struct TYPE_2__ {scalar_t__ feeding; int /*<<< orphan*/  feedlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,...) ; 
 int EINVAL ; 
 int cx18_stop_v4l2_encode_stream (struct cx18_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx18_dvb_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct cx18_stream *stream = (struct cx18_stream *)demux->priv;
	struct cx18 *cx;
	int ret = -EINVAL;

	if (stream) {
		cx = stream->cx;
		CX18_DEBUG_INFO("Stop feed: pid = 0x%x index = %d\n",
				feed->pid, feed->index);

		mutex_lock(&stream->dvb->feedlock);
		if (--stream->dvb->feeding == 0) {
			CX18_DEBUG_INFO("Stopping Transport DMA\n");
			mutex_lock(&cx->serialize_lock);
			ret = cx18_stop_v4l2_encode_stream(stream, 0);
			mutex_unlock(&cx->serialize_lock);
		} else
			ret = 0;
		mutex_unlock(&stream->dvb->feedlock);
	}

	return ret;
}