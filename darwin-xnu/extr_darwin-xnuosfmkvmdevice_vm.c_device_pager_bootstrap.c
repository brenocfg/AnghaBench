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
typedef  int vm_size_t ;
struct device_pager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAX_DNODE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 int /*<<< orphan*/  device_pager_lck_attr ; 
 int /*<<< orphan*/  device_pager_lck_grp ; 
 int /*<<< orphan*/  device_pager_lck_grp_attr ; 
 int /*<<< orphan*/  device_pager_zone ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zinit (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
device_pager_bootstrap(void)
{
	vm_size_t      size;

	size = (vm_size_t) sizeof(struct device_pager);
	device_pager_zone = zinit(size, (vm_size_t) MAX_DNODE*size,
				PAGE_SIZE, "device node pager structures");
	zone_change(device_pager_zone, Z_CALLERACCT, FALSE);

	lck_grp_attr_setdefault(&device_pager_lck_grp_attr);
	lck_grp_init(&device_pager_lck_grp, "device_pager", &device_pager_lck_grp_attr);
	lck_attr_setdefault(&device_pager_lck_attr);

	return;
}