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
typedef  scalar_t__ pool_initialize_func_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_POOL_INITIALIZE ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_COMMAND ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_VDEVS ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
lzc_initialize(const char *poolname, pool_initialize_func_t cmd_type,
    nvlist_t *vdevs, nvlist_t **errlist)
{
	int error;
	nvlist_t *args = fnvlist_alloc();
	fnvlist_add_uint64(args, ZPOOL_INITIALIZE_COMMAND, (uint64_t)cmd_type);
	fnvlist_add_nvlist(args, ZPOOL_INITIALIZE_VDEVS, vdevs);

	error = lzc_ioctl(ZFS_IOC_POOL_INITIALIZE, poolname, args, errlist);

	fnvlist_free(args);

	return (error);
}