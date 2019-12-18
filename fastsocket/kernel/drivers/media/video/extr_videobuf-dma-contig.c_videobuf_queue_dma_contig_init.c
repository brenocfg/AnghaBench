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
struct videobuf_queue_ops {int dummy; } ;
struct videobuf_queue {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  qops ; 
 int /*<<< orphan*/  videobuf_queue_core_init (struct videobuf_queue*,struct videobuf_queue_ops*,struct device*,int /*<<< orphan*/ *,int,int,unsigned int,void*,int /*<<< orphan*/ *) ; 

void videobuf_queue_dma_contig_init(struct videobuf_queue *q,
				    struct videobuf_queue_ops *ops,
				    struct device *dev,
				    spinlock_t *irqlock,
				    enum v4l2_buf_type type,
				    enum v4l2_field field,
				    unsigned int msize,
				    void *priv)
{
	videobuf_queue_core_init(q, ops, dev, irqlock, type, field, msize,
				 priv, &qops);
}