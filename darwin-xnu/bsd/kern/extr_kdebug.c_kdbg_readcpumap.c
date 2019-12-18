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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_2__ {int kdebug_flags; int /*<<< orphan*/  kdebug_cpus; int /*<<< orphan*/  kdebug_iops; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int KDBG_BUFINIT ; 
 int KERN_SUCCESS ; 
 scalar_t__ copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ kd_ctrl_page ; 
 int kdbg_cpumap_init_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int
kdbg_readcpumap(user_addr_t user_cpumap, size_t *user_cpumap_size)
{
	uint8_t* cpumap = NULL;
	uint32_t cpumap_size = 0;
	int ret = KERN_SUCCESS;

	if (kd_ctrl_page.kdebug_flags & KDBG_BUFINIT) {
		if (kdbg_cpumap_init_internal(kd_ctrl_page.kdebug_iops, kd_ctrl_page.kdebug_cpus, &cpumap, &cpumap_size) == KERN_SUCCESS) {
			if (user_cpumap) {
				size_t bytes_to_copy = (*user_cpumap_size >= cpumap_size) ? cpumap_size : *user_cpumap_size;
				if (copyout(cpumap, user_cpumap, (size_t)bytes_to_copy)) {
					ret = EFAULT;
				}
			}
			*user_cpumap_size = cpumap_size;
			kmem_free(kernel_map, (vm_offset_t)cpumap, cpumap_size);
		} else
			ret = EINVAL;
	} else
		ret = EINVAL;

	return (ret);
}