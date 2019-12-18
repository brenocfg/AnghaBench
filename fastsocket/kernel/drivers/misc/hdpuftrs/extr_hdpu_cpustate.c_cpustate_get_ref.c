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
struct TYPE_2__ {int excl; int /*<<< orphan*/  lock; scalar_t__ open_count; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__ cpustate ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpustate_get_ref(int excl)
{

	int retval = -EBUSY;

	spin_lock(&cpustate.lock);

	if (cpustate.excl)
		goto out_busy;

	if (excl) {
		if (cpustate.open_count)
			goto out_busy;
		cpustate.excl = 1;
	}

	cpustate.open_count++;
	retval = 0;

      out_busy:
	spin_unlock(&cpustate.lock);
	return retval;
}