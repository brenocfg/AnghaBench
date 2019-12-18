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
struct be_adapter {int flags; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int BE_FLAGS_WORKER_SCHEDULED ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_cancel_worker(struct be_adapter *adapter)
{
	if (adapter->flags & BE_FLAGS_WORKER_SCHEDULED) {
		cancel_delayed_work_sync(&adapter->work);
		adapter->flags &= ~BE_FLAGS_WORKER_SCHEDULED;
	}
}