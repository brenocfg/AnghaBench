#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {int reading; int /*<<< orphan*/  irqlock; TYPE_2__** bufs; TYPE_1__* ops; int /*<<< orphan*/  stream; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;
struct TYPE_4__ {int (* buf_prepare ) (struct videobuf_queue*,TYPE_2__*,int) ;int /*<<< orphan*/  (* buf_queue ) (struct videobuf_queue*,TYPE_2__*) ;int /*<<< orphan*/  (* buf_setup ) (struct videobuf_queue*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 unsigned int PAGE_ALIGN (unsigned int) ; 
 int /*<<< orphan*/  V4L2_MEMORY_USERPTR ; 
 unsigned int VIDEO_MAX_FRAME ; 
 int __videobuf_mmap_setup (struct videobuf_queue*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct videobuf_queue*,unsigned int*,unsigned int*) ; 
 int stub2 (struct videobuf_queue*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub3 (struct videobuf_queue*,TYPE_2__*) ; 
 int videobuf_next_field (struct videobuf_queue*) ; 

__attribute__((used)) static int __videobuf_read_start(struct videobuf_queue *q)
{
	enum v4l2_field field;
	unsigned long flags = 0;
	unsigned int count = 0, size = 0;
	int err, i;

	q->ops->buf_setup(q, &count, &size);
	if (count < 2)
		count = 2;
	if (count > VIDEO_MAX_FRAME)
		count = VIDEO_MAX_FRAME;
	size = PAGE_ALIGN(size);

	err = __videobuf_mmap_setup(q, count, size, V4L2_MEMORY_USERPTR);
	if (err < 0)
		return err;

	count = err;

	for (i = 0; i < count; i++) {
		field = videobuf_next_field(q);
		err = q->ops->buf_prepare(q, q->bufs[i], field);
		if (err)
			return err;
		list_add_tail(&q->bufs[i]->stream, &q->stream);
	}
	spin_lock_irqsave(q->irqlock, flags);
	for (i = 0; i < count; i++)
		q->ops->buf_queue(q, q->bufs[i]);
	spin_unlock_irqrestore(q->irqlock, flags);
	q->reading = 1;
	return 0;
}