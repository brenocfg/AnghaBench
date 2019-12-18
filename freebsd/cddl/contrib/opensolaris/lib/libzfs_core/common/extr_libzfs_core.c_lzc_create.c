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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  enum lzc_dataset_type { ____Placeholder_lzc_dataset_type } lzc_dataset_type ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_CREATE ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

int
lzc_create(const char *fsname, enum lzc_dataset_type type, nvlist_t *props)
{
	int error;
	nvlist_t *args = fnvlist_alloc();
	fnvlist_add_int32(args, "type", (dmu_objset_type_t)type);
	if (props != NULL)
		fnvlist_add_nvlist(args, "props", props);
	error = lzc_ioctl(ZFS_IOC_CREATE, fsname, args, NULL);
	nvlist_free(args);
	return (error);
}