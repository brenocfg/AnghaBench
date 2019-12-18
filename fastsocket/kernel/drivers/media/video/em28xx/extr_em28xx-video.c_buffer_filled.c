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
struct em28xx_dmaqueue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  done; int /*<<< orphan*/  queue; int /*<<< orphan*/  ts; int /*<<< orphan*/  field_count; int /*<<< orphan*/  state; int /*<<< orphan*/  i; } ;
struct em28xx_buffer {TYPE_2__ vb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vid_buf; } ;
struct em28xx {TYPE_1__ isoc_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  em28xx_isocdbg (char*,struct em28xx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void buffer_filled(struct em28xx *dev,
				  struct em28xx_dmaqueue *dma_q,
				  struct em28xx_buffer *buf)
{
	/* Advice that buffer was filled */
	em28xx_isocdbg("[%p/%d] wakeup\n", buf, buf->vb.i);
	buf->vb.state = VIDEOBUF_DONE;
	buf->vb.field_count++;
	do_gettimeofday(&buf->vb.ts);

	dev->isoc_ctl.vid_buf = NULL;

	list_del(&buf->vb.queue);
	wake_up(&buf->vb.done);
}