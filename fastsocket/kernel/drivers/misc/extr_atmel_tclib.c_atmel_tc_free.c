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
struct atmel_tc {int /*<<< orphan*/ * iomem; int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_list_lock ; 

void atmel_tc_free(struct atmel_tc *tc)
{
	spin_lock(&tc_list_lock);
	if (tc->regs) {
		iounmap(tc->regs);
		release_resource(tc->iomem);
		tc->regs = NULL;
		tc->iomem = NULL;
	}
	spin_unlock(&tc_list_lock);
}