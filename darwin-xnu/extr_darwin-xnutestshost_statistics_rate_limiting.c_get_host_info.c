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
struct all_host_info {int /*<<< orphan*/  host_expired_task_info2; int /*<<< orphan*/  host_expired_task_info; int /*<<< orphan*/  host_cpu_load_info; int /*<<< orphan*/  host_vm_info_rev2; int /*<<< orphan*/  host_vm_info_rev1; int /*<<< orphan*/  host_vm_info_rev0; int /*<<< orphan*/  host_load_info; int /*<<< orphan*/  host_extmod_info64; int /*<<< orphan*/  host_vm_info64_rev1; int /*<<< orphan*/  host_vm_info64_rev0; } ;
typedef  int /*<<< orphan*/  host_t ;
typedef  int /*<<< orphan*/  host_info_t ;
typedef  int /*<<< orphan*/  host_info64_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CPU_LOAD_INFO ; 
 unsigned int HOST_CPU_LOAD_INFO_COUNT ; 
 int /*<<< orphan*/  HOST_EXPIRED_TASK_INFO ; 
 int /*<<< orphan*/  HOST_EXTMOD_INFO64 ; 
 unsigned int HOST_EXTMOD_INFO64_COUNT ; 
 int /*<<< orphan*/  HOST_LOAD_INFO ; 
 unsigned int HOST_LOAD_INFO_COUNT ; 
 int /*<<< orphan*/  HOST_VM_INFO ; 
 int /*<<< orphan*/  HOST_VM_INFO64 ; 
 unsigned int HOST_VM_INFO64_REV0_COUNT ; 
 unsigned int HOST_VM_INFO64_REV1_COUNT ; 
 unsigned int HOST_VM_INFO_REV0_COUNT ; 
 unsigned int HOST_VM_INFO_REV1_COUNT ; 
 unsigned int HOST_VM_INFO_REV2_COUNT ; 
 unsigned int TASK_POWER_INFO_COUNT ; 
 unsigned int TASK_POWER_INFO_V2_COUNT ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  host_statistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  host_statistics64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void
get_host_info(struct all_host_info* data, host_t self, int iter){
	int i;
	unsigned int count;
	for (i = 0; i < iter; i++){
		count = HOST_VM_INFO64_REV0_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics64(self, HOST_VM_INFO64, (host_info64_t)&data[i].host_vm_info64_rev0, &count), NULL);
		count = HOST_VM_INFO64_REV1_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics64(self, HOST_VM_INFO64, (host_info64_t)&data[i].host_vm_info64_rev1, &count), NULL);
		count = HOST_EXTMOD_INFO64_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics64(self, HOST_EXTMOD_INFO64, (host_info64_t)&data[i].host_extmod_info64, &count), NULL);
		count = HOST_LOAD_INFO_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_LOAD_INFO, (host_info_t)&data[i].host_load_info, &count), NULL);
		count = HOST_VM_INFO_REV0_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_VM_INFO, (host_info_t)&data[i].host_vm_info_rev0, &count), NULL);
		count = HOST_VM_INFO_REV1_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_VM_INFO, (host_info_t)&data[i].host_vm_info_rev1, &count), NULL);
		count = HOST_VM_INFO_REV2_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_VM_INFO, (host_info_t)&data[i].host_vm_info_rev2, &count), NULL);
		count = HOST_CPU_LOAD_INFO_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_CPU_LOAD_INFO, (host_info_t)&data[i].host_cpu_load_info, &count), NULL);
		count = TASK_POWER_INFO_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_EXPIRED_TASK_INFO, (host_info_t)&data[i].host_expired_task_info, &count), NULL);
		count = TASK_POWER_INFO_V2_COUNT;
		T_QUIET;T_ASSERT_POSIX_ZERO(host_statistics(self, HOST_EXPIRED_TASK_INFO, (host_info_t)&data[i].host_expired_task_info2, &count), NULL);

	}

}