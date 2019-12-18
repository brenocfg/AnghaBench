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
typedef  size_t zpool_status_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 size_t NMSGID ; 
 size_t check_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** zfs_msgid_table ; 

zpool_status_t
zpool_import_status(nvlist_t *config, char **msgid)
{
	zpool_status_t ret = check_status(config, B_TRUE);

	if (ret >= NMSGID)
		*msgid = NULL;
	else
		*msgid = zfs_msgid_table[ret];

	return (ret);
}