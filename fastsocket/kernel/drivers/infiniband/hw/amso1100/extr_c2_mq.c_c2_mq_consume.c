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
typedef  void c2wr_hdr ;
struct TYPE_2__ {void* host; } ;
struct c2_mq {scalar_t__ magic; scalar_t__ type; int priv; int msg_size; TYPE_1__ msg_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ C2_MQ_HOST_TARGET ; 
 scalar_t__ C2_MQ_MAGIC ; 
 int /*<<< orphan*/  CCWR_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ c2_mq_empty (struct c2_mq*) ; 

void *c2_mq_consume(struct c2_mq *q)
{
	BUG_ON(q->magic != C2_MQ_MAGIC);
	BUG_ON(q->type != C2_MQ_HOST_TARGET);

	if (c2_mq_empty(q)) {
		return NULL;
	} else {
#ifdef DEBUG
		struct c2wr_hdr *m = (struct c2wr_hdr *)
		    (q->msg_pool.host + q->priv * q->msg_size);
#ifdef CCMSGMAGIC
		BUG_ON(m->magic != be32_to_cpu(CCWR_MAGIC));
#endif
		return m;
#else
		return q->msg_pool.host + q->priv * q->msg_size;
#endif
	}
}