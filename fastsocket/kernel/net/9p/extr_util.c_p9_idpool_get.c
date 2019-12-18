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
struct p9_idpool {int /*<<< orphan*/  lock; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int,struct p9_idpool*) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct p9_idpool*,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int p9_idpool_get(struct p9_idpool *p)
{
	int i = 0;
	int error;
	unsigned long flags;

retry:
	if (idr_pre_get(&p->pool, GFP_KERNEL) == 0)
		return 0;

	spin_lock_irqsave(&p->lock, flags);

	/* no need to store exactly p, we just need something non-null */
	error = idr_get_new(&p->pool, p, &i);
	spin_unlock_irqrestore(&p->lock, flags);

	if (error == -EAGAIN)
		goto retry;
	else if (error)
		return -1;

	P9_DPRINTK(P9_DEBUG_MUX, " id %d pool %p\n", i, p);
	return i;
}