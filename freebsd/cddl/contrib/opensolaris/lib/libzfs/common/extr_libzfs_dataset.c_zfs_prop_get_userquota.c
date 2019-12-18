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
typedef  scalar_t__ zfs_userquota_prop_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ ZFS_PROP_GROUPQUOTA ; 
 scalar_t__ ZFS_PROP_USERQUOTA ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_nicenum (scalar_t__,char*,int) ; 
 int zfs_prop_get_userquota_common (int /*<<< orphan*/ *,char const*,scalar_t__*,scalar_t__*) ; 

int
zfs_prop_get_userquota(zfs_handle_t *zhp, const char *propname,
    char *propbuf, int proplen, boolean_t literal)
{
	int err;
	uint64_t propvalue;
	zfs_userquota_prop_t type;

	err = zfs_prop_get_userquota_common(zhp, propname, &propvalue,
	    &type);

	if (err)
		return (err);

	if (literal) {
		(void) snprintf(propbuf, proplen, "%llu", propvalue);
	} else if (propvalue == 0 &&
	    (type == ZFS_PROP_USERQUOTA || type == ZFS_PROP_GROUPQUOTA)) {
		(void) strlcpy(propbuf, "none", proplen);
	} else {
		zfs_nicenum(propvalue, propbuf, proplen);
	}
	return (0);
}