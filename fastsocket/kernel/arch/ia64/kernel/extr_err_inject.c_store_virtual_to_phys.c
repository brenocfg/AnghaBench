#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sysdev_attribute {int dummy; } ;
struct sys_device {unsigned int id; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  VM_READ ; 
 TYPE_1__* current ; 
 int get_user_pages (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ia64_tpa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * phys_addr ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoull (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t
store_virtual_to_phys(struct sys_device *dev, struct sysdev_attribute *attr,
			const char *buf, size_t size)
{
	unsigned int cpu=dev->id;
	u64 virt_addr=simple_strtoull(buf, NULL, 16);
	int ret;

        ret = get_user_pages(current, current->mm, virt_addr,
                        1, VM_READ, 0, NULL, NULL);
	if (ret<=0) {
#ifdef ERR_INJ_DEBUG
		printk("Virtual address %lx is not existing.\n",virt_addr);
#endif
		return -EINVAL;
	}

	phys_addr[cpu] = ia64_tpa(virt_addr);
	return size;
}