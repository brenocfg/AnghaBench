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
 int EPERM ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 scalar_t__ ktrace_owning_unique_id ; 
 scalar_t__ proc_uniqueid (int /*<<< orphan*/ ) ; 

int
ktrace_read_check(void)
{
	ktrace_assert_lock_held();

	if (proc_uniqueid(current_proc()) == ktrace_owning_unique_id)
	{
		return 0;
	}

	return kauth_cred_issuser(kauth_cred_get()) ? 0 : EPERM;
}