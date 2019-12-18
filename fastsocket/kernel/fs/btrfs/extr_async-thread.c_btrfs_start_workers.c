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
struct btrfs_workers {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_workers_starting; } ;

/* Variables and functions */
 int __btrfs_start_workers (struct btrfs_workers*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int btrfs_start_workers(struct btrfs_workers *workers)
{
	spin_lock_irq(&workers->lock);
	workers->num_workers_starting++;
	spin_unlock_irq(&workers->lock);
	return __btrfs_start_workers(workers);
}