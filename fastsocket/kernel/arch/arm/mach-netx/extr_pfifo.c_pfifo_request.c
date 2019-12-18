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

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NETX_PFIFO_RESET ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfifo_lock ; 
 unsigned int pfifo_used ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

int pfifo_request(unsigned int pfifo_mask)
{
	int err = 0;
	unsigned int val;

	mutex_lock(&pfifo_lock);

	if (pfifo_mask & pfifo_used) {
		err = -EBUSY;
		goto out;
	}

	pfifo_used |= pfifo_mask;

	val = readl(NETX_PFIFO_RESET);
	writel(val | pfifo_mask, NETX_PFIFO_RESET);
	writel(val, NETX_PFIFO_RESET);

out:
	mutex_unlock(&pfifo_lock);
	return err;
}