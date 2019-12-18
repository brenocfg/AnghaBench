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
typedef  int /*<<< orphan*/  pool ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_SNAPSHOT ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int
lzc_snapshot(nvlist_t *snaps, nvlist_t *props, nvlist_t **errlist)
{
	nvpair_t *elem;
	nvlist_t *args;
	int error;
	char pool[ZFS_MAX_DATASET_NAME_LEN];

	*errlist = NULL;

	/* determine the pool name */
	elem = nvlist_next_nvpair(snaps, NULL);
	if (elem == NULL)
		return (0);
	(void) strlcpy(pool, nvpair_name(elem), sizeof (pool));
	pool[strcspn(pool, "/@")] = '\0';

	args = fnvlist_alloc();
	fnvlist_add_nvlist(args, "snaps", snaps);
	if (props != NULL)
		fnvlist_add_nvlist(args, "props", props);

	error = lzc_ioctl(ZFS_IOC_SNAPSHOT, pool, args, errlist);
	nvlist_free(args);

	return (error);
}