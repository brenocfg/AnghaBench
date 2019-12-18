#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  zfs_prop_t ;
struct TYPE_5__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_type; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_PROPTYPE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_numeric_property (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_source (TYPE_1__*,int /*<<< orphan*/ *,char*,char*,size_t) ; 
 int zfs_error_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_prop_get_numeric(zfs_handle_t *zhp, zfs_prop_t prop, uint64_t *value,
    zprop_source_t *src, char *statbuf, size_t statlen)
{
	char *source;

	/*
	 * Check to see if this property applies to our object
	 */
	if (!zfs_prop_valid_for_type(prop, zhp->zfs_type)) {
		return (zfs_error_fmt(zhp->zfs_hdl, EZFS_PROPTYPE,
		    dgettext(TEXT_DOMAIN, "cannot get property '%s'"),
		    zfs_prop_to_name(prop)));
	}

	if (src)
		*src = ZPROP_SRC_NONE;

	if (get_numeric_property(zhp, prop, src, &source, value) != 0)
		return (-1);

	get_source(zhp, src, source, statbuf, statlen);

	return (0);
}