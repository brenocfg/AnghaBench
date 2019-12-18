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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void** consumer; void** producer; } ;
struct aac_queue {int entries; TYPE_1__ headers; int /*<<< orphan*/  lockdata; int /*<<< orphan*/ * lock; int /*<<< orphan*/  qfull; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  cmdready; struct aac_dev* dev; scalar_t__ numpending; } ;
struct aac_dev {int dummy; } ;
typedef  void* __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aac_queue_init(struct aac_dev * dev, struct aac_queue * q, u32 *mem, int qsize)
{
	q->numpending = 0;
	q->dev = dev;
	init_waitqueue_head(&q->cmdready);
	INIT_LIST_HEAD(&q->cmdq);
	init_waitqueue_head(&q->qfull);
	spin_lock_init(&q->lockdata);
	q->lock = &q->lockdata;
	q->headers.producer = (__le32 *)mem;
	q->headers.consumer = (__le32 *)(mem+1);
	*(q->headers.producer) = cpu_to_le32(qsize);
	*(q->headers.consumer) = cpu_to_le32(qsize);
	q->entries = qsize;
}