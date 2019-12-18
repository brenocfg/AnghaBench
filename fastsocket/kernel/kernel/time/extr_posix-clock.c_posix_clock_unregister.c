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
struct posix_clock {int zombie; int /*<<< orphan*/  kref; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_clock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void posix_clock_unregister(struct posix_clock *clk)
{
	cdev_del(&clk->cdev);

	down_write(&clk->rwsem);
	clk->zombie = true;
	up_write(&clk->rwsem);

	kref_put(&clk->kref, delete_clock);
}