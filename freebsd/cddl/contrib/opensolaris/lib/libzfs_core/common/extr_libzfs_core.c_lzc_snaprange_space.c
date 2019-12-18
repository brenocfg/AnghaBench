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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fs ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ZFS_IOC_SPACE_SNAPS ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_lookup_uint64 (int /*<<< orphan*/ *,char*) ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

int
lzc_snaprange_space(const char *firstsnap, const char *lastsnap,
    uint64_t *usedp)
{
	nvlist_t *args;
	nvlist_t *result;
	int err;
	char fs[ZFS_MAX_DATASET_NAME_LEN];
	char *atp;

	/* determine the fs name */
	(void) strlcpy(fs, firstsnap, sizeof (fs));
	atp = strchr(fs, '@');
	if (atp == NULL)
		return (EINVAL);
	*atp = '\0';

	args = fnvlist_alloc();
	fnvlist_add_string(args, "firstsnap", firstsnap);

	err = lzc_ioctl(ZFS_IOC_SPACE_SNAPS, lastsnap, args, &result);
	nvlist_free(args);
	if (err == 0)
		*usedp = fnvlist_lookup_uint64(result, "used");
	fnvlist_free(result);

	return (err);
}