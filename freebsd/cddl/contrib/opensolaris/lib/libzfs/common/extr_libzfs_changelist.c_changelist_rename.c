#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_6__* cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
struct TYPE_9__ {int /*<<< orphan*/  cl_list; } ;
typedef  TYPE_2__ prop_changelist_t ;
typedef  int /*<<< orphan*/  newname ;
struct TYPE_10__ {char* zfs_name; } ;

/* Variables and functions */
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  isa_child_of (char*,char const*) ; 
 int /*<<< orphan*/  remove_mountpoint (TYPE_6__*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 TYPE_1__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_list_next (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
changelist_rename(prop_changelist_t *clp, const char *src, const char *dst)
{
	prop_changenode_t *cn;
	char newname[ZFS_MAX_DATASET_NAME_LEN];

	for (cn = uu_list_first(clp->cl_list); cn != NULL;
	    cn = uu_list_next(clp->cl_list, cn)) {
		/*
		 * Do not rename a clone that's not in the source hierarchy.
		 */
		if (!isa_child_of(cn->cn_handle->zfs_name, src))
			continue;

		/*
		 * Destroy the previous mountpoint if needed.
		 */
		remove_mountpoint(cn->cn_handle);

		(void) strlcpy(newname, dst, sizeof (newname));
		(void) strcat(newname, cn->cn_handle->zfs_name + strlen(src));

		(void) strlcpy(cn->cn_handle->zfs_name, newname,
		    sizeof (cn->cn_handle->zfs_name));
	}
}