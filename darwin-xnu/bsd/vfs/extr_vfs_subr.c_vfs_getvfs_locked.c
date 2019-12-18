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
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  fsid_t ;

/* Variables and functions */
 struct mount* mount_list_lookupby_fsid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mount *
vfs_getvfs_locked(fsid_t *fsid)
{
	return(mount_list_lookupby_fsid(fsid, 1, 0));
}