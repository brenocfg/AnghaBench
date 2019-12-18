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
struct TYPE_3__ {int /*<<< orphan*/  group_name; } ;
typedef  TYPE_1__ FDFSStorageIdInfo ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 TYPE_1__* fdfs_get_storage_by_id (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int fdfs_check_storage_id(const char *group_name, const char *id)
{
	FDFSStorageIdInfo *pFound;

	pFound = fdfs_get_storage_by_id(id);
	if (pFound == NULL)
	{
		return ENOENT;
	}

	return strcmp(pFound->group_name, group_name) == 0 ? 0 : EINVAL;
}