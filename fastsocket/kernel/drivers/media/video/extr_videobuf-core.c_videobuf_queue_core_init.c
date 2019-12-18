#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct videobuf_queue_ops {int /*<<< orphan*/  buf_release; int /*<<< orphan*/  buf_queue; int /*<<< orphan*/  buf_prepare; int /*<<< orphan*/  buf_setup; } ;
struct videobuf_queue {int type; int field; unsigned int msize; int /*<<< orphan*/  stream; int /*<<< orphan*/  wait; int /*<<< orphan*/  vb_lock; struct videobuf_qtype_ops* int_ops; struct videobuf_queue_ops const* ops; void* priv_data; struct device* dev; struct mutex* ext_lock; int /*<<< orphan*/ * irqlock; } ;
struct videobuf_qtype_ops {int dummy; } ;
struct mutex {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct videobuf_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void videobuf_queue_core_init(struct videobuf_queue *q,
			 const struct videobuf_queue_ops *ops,
			 struct device *dev,
			 spinlock_t *irqlock,
			 enum v4l2_buf_type type,
			 enum v4l2_field field,
			 unsigned int msize,
			 void *priv,
			 struct videobuf_qtype_ops *int_ops,
			 struct mutex *ext_lock)
{
	BUG_ON(!q);
	memset(q, 0, sizeof(*q));
	q->irqlock   = irqlock;
	q->ext_lock  = ext_lock;
	q->dev       = dev;
	q->type      = type;
	q->field     = field;
	q->msize     = msize;
	q->ops       = ops;
	q->priv_data = priv;
	q->int_ops   = int_ops;

	/* All buffer operations are mandatory */
	BUG_ON(!q->ops->buf_setup);
	BUG_ON(!q->ops->buf_prepare);
	BUG_ON(!q->ops->buf_queue);
	BUG_ON(!q->ops->buf_release);

	/* Lock is mandatory for queue_cancel to work */
	BUG_ON(!irqlock);

	/* Having implementations for abstract methods are mandatory */
	BUG_ON(!q->int_ops);

	mutex_init(&q->vb_lock);
	init_waitqueue_head(&q->wait);
	INIT_LIST_HEAD(&q->stream);
}