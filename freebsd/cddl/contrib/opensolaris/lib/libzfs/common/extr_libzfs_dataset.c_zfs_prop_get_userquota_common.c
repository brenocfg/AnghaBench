#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_userquota_prop_t ;
struct TYPE_8__ {TYPE_1__* zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_2__ zfs_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_objset_type; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  libzfs_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_USERSPACE_ONE ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int userquota_propname_decode (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_get_int (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_prop_get_userquota_common(zfs_handle_t *zhp, const char *propname,
    uint64_t *propvalue, zfs_userquota_prop_t *typep)
{
	int err;
	zfs_cmd_t zc = { 0 };

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));

	err = userquota_propname_decode(propname,
	    zfs_prop_get_int(zhp, ZFS_PROP_ZONED),
	    typep, zc.zc_value, sizeof (zc.zc_value), &zc.zc_guid);
	zc.zc_objset_type = *typep;
	if (err)
		return (err);

	err = ioctl(zhp->zfs_hdl->libzfs_fd, ZFS_IOC_USERSPACE_ONE, &zc);
	if (err)
		return (err);

	*propvalue = zc.zc_cookie;
	return (0);
}