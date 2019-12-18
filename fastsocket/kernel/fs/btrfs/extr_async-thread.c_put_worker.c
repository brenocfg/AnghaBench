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
struct btrfs_worker_thread {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct btrfs_worker_thread*) ; 

__attribute__((used)) static void put_worker(struct btrfs_worker_thread *worker)
{
	if (atomic_dec_and_test(&worker->refs))
		kfree(worker);
}