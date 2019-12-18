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
typedef  int u32 ;
struct cxio_rdev {int qpmask; TYPE_1__* rscp; } ;
struct TYPE_2__ {int /*<<< orphan*/  qpid_fifo; int /*<<< orphan*/  qpid_fifo_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int T3_MAX_NUM_QP ; 
 int /*<<< orphan*/  __kfifo_put (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  kfifo_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxio_init_qpid_fifo(struct cxio_rdev *rdev_p)
{
	u32 i;

	spin_lock_init(&rdev_p->rscp->qpid_fifo_lock);

	rdev_p->rscp->qpid_fifo = kfifo_alloc(T3_MAX_NUM_QP * sizeof(u32),
					      GFP_KERNEL,
					      &rdev_p->rscp->qpid_fifo_lock);
	if (IS_ERR(rdev_p->rscp->qpid_fifo))
		return -ENOMEM;

	for (i = 16; i < T3_MAX_NUM_QP; i++)
		if (!(i & rdev_p->qpmask))
			__kfifo_put(rdev_p->rscp->qpid_fifo,
				    (unsigned char *) &i, sizeof(u32));
	return 0;
}