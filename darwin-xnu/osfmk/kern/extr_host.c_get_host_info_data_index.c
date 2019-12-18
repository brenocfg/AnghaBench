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
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int host_flavor_t ;

/* Variables and functions */
#define  HOST_CPU_LOAD_INFO 133 
 int /*<<< orphan*/  HOST_CPU_LOAD_INFO_COUNT ; 
 int HOST_CPU_LOAD_INFO_REV0 ; 
#define  HOST_EXPIRED_TASK_INFO 132 
 int HOST_EXPIRED_TASK_INFO_REV0 ; 
 int HOST_EXPIRED_TASK_INFO_REV1 ; 
#define  HOST_EXTMOD_INFO64 131 
 int /*<<< orphan*/  HOST_EXTMOD_INFO64_COUNT ; 
 int HOST_EXTMOD_INFO64_REV0 ; 
#define  HOST_LOAD_INFO 130 
 int /*<<< orphan*/  HOST_LOAD_INFO_COUNT ; 
 int HOST_LOAD_INFO_REV0 ; 
#define  HOST_VM_INFO 129 
#define  HOST_VM_INFO64 128 
 int HOST_VM_INFO64_REV0 ; 
 int /*<<< orphan*/  HOST_VM_INFO64_REV0_COUNT ; 
 int HOST_VM_INFO64_REV1 ; 
 int /*<<< orphan*/  HOST_VM_INFO64_REV1_COUNT ; 
 int HOST_VM_INFO_REV0 ; 
 int /*<<< orphan*/  HOST_VM_INFO_REV0_COUNT ; 
 int HOST_VM_INFO_REV1 ; 
 int /*<<< orphan*/  HOST_VM_INFO_REV1_COUNT ; 
 int HOST_VM_INFO_REV2 ; 
 int /*<<< orphan*/  HOST_VM_INFO_REV2_COUNT ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  TASK_POWER_INFO_COUNT ; 
 int /*<<< orphan*/  TASK_POWER_INFO_V2_COUNT ; 

__attribute__((used)) static int
get_host_info_data_index(bool is_stat64, host_flavor_t flavor, mach_msg_type_number_t* count, kern_return_t* ret)
{
	switch (flavor) {

        case HOST_VM_INFO64:
	if (!is_stat64){
		*ret = KERN_INVALID_ARGUMENT;
		return -1;
	}
	if (*count < HOST_VM_INFO64_REV0_COUNT) {
		*ret = KERN_FAILURE;
		return -1;
	}
	if (*count >= HOST_VM_INFO64_REV1_COUNT) {
		return HOST_VM_INFO64_REV1;
	}
	return HOST_VM_INFO64_REV0;

	case HOST_EXTMOD_INFO64:
	if (!is_stat64){
		*ret = KERN_INVALID_ARGUMENT;
		return -1;
	}
	if (*count < HOST_EXTMOD_INFO64_COUNT) {
		*ret = KERN_FAILURE;
		return -1;
	}
	return HOST_EXTMOD_INFO64_REV0;

	case HOST_LOAD_INFO:
	if (*count < HOST_LOAD_INFO_COUNT) {
		*ret = KERN_FAILURE;
		return -1;
	}
	return HOST_LOAD_INFO_REV0;

	case HOST_VM_INFO:
	if (*count < HOST_VM_INFO_REV0_COUNT) {
		*ret = KERN_FAILURE;
		return -1;
	}
	if (*count >= HOST_VM_INFO_REV2_COUNT) {
		return HOST_VM_INFO_REV2;
	}
	if (*count >= HOST_VM_INFO_REV1_COUNT) {
		return HOST_VM_INFO_REV1;
	}
	return HOST_VM_INFO_REV0;

	case HOST_CPU_LOAD_INFO:
	if (*count < HOST_CPU_LOAD_INFO_COUNT) {
		*ret = KERN_FAILURE;
		return -1;
	}
	return HOST_CPU_LOAD_INFO_REV0;

	case HOST_EXPIRED_TASK_INFO:
	if (*count < TASK_POWER_INFO_COUNT){
		*ret = KERN_FAILURE;
		return -1;
	}
	if (*count >= TASK_POWER_INFO_V2_COUNT){
		return HOST_EXPIRED_TASK_INFO_REV1;
	}
	return HOST_EXPIRED_TASK_INFO_REV0;

	default:
	*ret = KERN_INVALID_ARGUMENT;
	return -1;

	}

}