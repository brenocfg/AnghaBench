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
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_active_sessions_lock ; 
 int ci_num_active_sessions ; 

void CiDecrementNumActiveSessions()
{
	Lock(ci_active_sessions_lock);
	{
		if (ci_num_active_sessions >= 1)
		{
			ci_num_active_sessions--;
		}
	}
	Unlock(ci_active_sessions_lock);
}