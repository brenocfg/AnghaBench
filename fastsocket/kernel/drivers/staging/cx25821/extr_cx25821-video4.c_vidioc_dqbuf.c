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
struct v4l2_buffer {int /*<<< orphan*/  sequence; } ;
struct file {int f_flags; } ;
struct cx25821_fh {struct cx25821_dev* dev; } ;
struct cx25821_dev {TYPE_1__* vidq; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 size_t SRAM_CH04 ; 
 int /*<<< orphan*/  get_queue (struct cx25821_fh*) ; 
 int videobuf_dqbuf (int /*<<< orphan*/ ,struct v4l2_buffer*,int) ; 

__attribute__((used)) static int vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	int ret_val = 0;
	struct cx25821_fh *fh = priv;
	struct cx25821_dev *dev = ((struct cx25821_fh *)priv)->dev;

	ret_val = videobuf_dqbuf(get_queue(fh), p, file->f_flags & O_NONBLOCK);

	p->sequence = dev->vidq[SRAM_CH04].count;

	return ret_val;
}