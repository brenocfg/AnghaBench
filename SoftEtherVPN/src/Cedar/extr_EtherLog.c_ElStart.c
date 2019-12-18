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
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewEl () ; 
 int /*<<< orphan*/  OSSetHighPriority () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el ; 
 int /*<<< orphan*/  el_lock ; 

void ElStart()
{
	// Raise the priority
	OSSetHighPriority();

	Lock(el_lock);
	{
		el = NewEl();
	}
	Unlock(el_lock);
}