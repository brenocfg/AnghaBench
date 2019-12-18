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
struct TYPE_2__ {int /*<<< orphan*/ * complete; scalar_t__ error; scalar_t__ done; int /*<<< orphan*/  working; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 TYPE_1__ suspend_data ; 
 int /*<<< orphan*/  suspend_work ; 
 int suspending ; 

__attribute__((used)) static int pseries_prepare_late(void)
{
	suspending = 1;
	atomic_set(&suspend_data.working, 0);
	suspend_data.done = 0;
	suspend_data.error = 0;
	suspend_data.complete = &suspend_work;
	INIT_COMPLETION(suspend_work);

	/* Ensure suspending and suspend_data.done is seen on all CPUs */
	mb();
	return 0;
}