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
typedef  int /*<<< orphan*/  fsname ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_get_bookmarks (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

boolean_t
zfs_bookmark_exists(const char *path)
{
	nvlist_t *bmarks;
	nvlist_t *props;
	char fsname[ZFS_MAX_DATASET_NAME_LEN];
	char *bmark_name;
	char *pound;
	int err;
	boolean_t rv;


	(void) strlcpy(fsname, path, sizeof (fsname));
	pound = strchr(fsname, '#');
	if (pound == NULL)
		return (B_FALSE);

	*pound = '\0';
	bmark_name = pound + 1;
	props = fnvlist_alloc();
	err = lzc_get_bookmarks(fsname, props, &bmarks);
	nvlist_free(props);
	if (err != 0) {
		nvlist_free(bmarks);
		return (B_FALSE);
	}

	rv = nvlist_exists(bmarks, bmark_name);
	nvlist_free(bmarks);
	return (rv);
}