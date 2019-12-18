#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_7__ {int /*<<< orphan*/ * zfs_recvd_props; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ get_recvd_props_ioctl (TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 int zfs_prop_get (TYPE_1__*,scalar_t__,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_set_recvd_props_mode (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_unset_recvd_props_mode (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
zfs_prop_get_recvd(zfs_handle_t *zhp, const char *propname, char *propbuf,
    size_t proplen, boolean_t literal)
{
	zfs_prop_t prop;
	int err = 0;

	if (zhp->zfs_recvd_props == NULL)
		if (get_recvd_props_ioctl(zhp) != 0)
			return (-1);

	prop = zfs_name_to_prop(propname);

	if (prop != ZPROP_INVAL) {
		uint64_t cookie;
		if (!nvlist_exists(zhp->zfs_recvd_props, propname))
			return (-1);
		zfs_set_recvd_props_mode(zhp, &cookie);
		err = zfs_prop_get(zhp, prop, propbuf, proplen,
		    NULL, NULL, 0, literal);
		zfs_unset_recvd_props_mode(zhp, &cookie);
	} else {
		nvlist_t *propval;
		char *recvdval;
		if (nvlist_lookup_nvlist(zhp->zfs_recvd_props,
		    propname, &propval) != 0)
			return (-1);
		verify(nvlist_lookup_string(propval, ZPROP_VALUE,
		    &recvdval) == 0);
		(void) strlcpy(propbuf, recvdval, proplen);
	}

	return (err == 0 ? 0 : -1);
}