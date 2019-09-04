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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  new_value ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
set_memorystatus_vm_map_fork_pidwatch(pid_t pid)
{
	uint64_t new_value = (uint64_t)pid;
	size_t new_len = sizeof(new_value);
	int err;

	err = sysctlbyname("kern.memorystatus_vm_map_fork_pidwatch", NULL, NULL, &new_value, new_len);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(err, "set sysctlbyname(kern.memorystatus_vm_map_fork_pidwatch...) failed");
	return;
}