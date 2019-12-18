#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cx231xx_dmaqueue {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  done; int /*<<< orphan*/  queue; int /*<<< orphan*/  ts; int /*<<< orphan*/  field_count; int /*<<< orphan*/  state; int /*<<< orphan*/  i; } ;
struct cx231xx_buffer {TYPE_4__ vb; } ;
struct TYPE_6__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {TYPE_2__ bulk_ctl; TYPE_1__ isoc_ctl; } ;
struct cx231xx {TYPE_3__ video_mode; scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  cx231xx_isocdbg (char*,struct cx231xx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void buffer_filled(struct cx231xx *dev,
				 struct cx231xx_dmaqueue *dma_q,
				 struct cx231xx_buffer *buf)
{
	/* Advice that buffer was filled */
	cx231xx_isocdbg("[%p/%d] wakeup\n", buf, buf->vb.i);
	buf->vb.state = VIDEOBUF_DONE;
	buf->vb.field_count++;
	do_gettimeofday(&buf->vb.ts);

	if (dev->USE_ISO)
		dev->video_mode.isoc_ctl.buf = NULL;
	else
		dev->video_mode.bulk_ctl.buf = NULL;

	list_del(&buf->vb.queue);
	wake_up(&buf->vb.done);
}