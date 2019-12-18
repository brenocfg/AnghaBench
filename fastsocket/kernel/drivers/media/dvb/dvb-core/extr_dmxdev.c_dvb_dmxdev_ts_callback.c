#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_ringbuffer {int error; int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {scalar_t__ output; } ;
struct TYPE_5__ {TYPE_1__ pes; } ;
struct dmxdev_filter {TYPE_3__* dev; struct dvb_ringbuffer buffer; TYPE_2__ params; } ;
struct dmx_ts_feed {struct dmxdev_filter* priv; } ;
typedef  enum dmx_success { ____Placeholder_dmx_success } dmx_success ;
struct TYPE_6__ {int /*<<< orphan*/  lock; struct dvb_ringbuffer dvr_buffer; } ;

/* Variables and functions */
 scalar_t__ DMX_OUT_DECODER ; 
 scalar_t__ DMX_OUT_TAP ; 
 scalar_t__ DMX_OUT_TSDEMUX_TAP ; 
 int dvb_dmxdev_buffer_write (struct dvb_ringbuffer*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  dvb_ringbuffer_flush (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_dmxdev_ts_callback(const u8 *buffer1, size_t buffer1_len,
				  const u8 *buffer2, size_t buffer2_len,
				  struct dmx_ts_feed *feed,
				  enum dmx_success success)
{
	struct dmxdev_filter *dmxdevfilter = feed->priv;
	struct dvb_ringbuffer *buffer;
	int ret;

	spin_lock(&dmxdevfilter->dev->lock);
	if (dmxdevfilter->params.pes.output == DMX_OUT_DECODER) {
		spin_unlock(&dmxdevfilter->dev->lock);
		return 0;
	}

	if (dmxdevfilter->params.pes.output == DMX_OUT_TAP
	    || dmxdevfilter->params.pes.output == DMX_OUT_TSDEMUX_TAP)
		buffer = &dmxdevfilter->buffer;
	else
		buffer = &dmxdevfilter->dev->dvr_buffer;
	if (buffer->error) {
		spin_unlock(&dmxdevfilter->dev->lock);
		wake_up(&buffer->queue);
		return 0;
	}
	ret = dvb_dmxdev_buffer_write(buffer, buffer1, buffer1_len);
	if (ret == buffer1_len)
		ret = dvb_dmxdev_buffer_write(buffer, buffer2, buffer2_len);
	if (ret < 0) {
		dvb_ringbuffer_flush(buffer);
		buffer->error = ret;
	}
	spin_unlock(&dmxdevfilter->dev->lock);
	wake_up(&buffer->queue);
	return 0;
}