#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pl_prop; char* pl_width; struct TYPE_4__* pl_next; int /*<<< orphan*/  pl_user_prop; } ;
typedef  TYPE_1__ zprop_list_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  property ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_5__ {scalar_t__ cb_scripted; int /*<<< orphan*/  cb_literal; TYPE_1__* cb_proplist; } ;
typedef  TYPE_2__ list_cbdata_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int ZFS_MAXPROPLEN ; 
 scalar_t__ ZFS_PROP_NAME ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_get_user_props (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_align_right (scalar_t__) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_userquota (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_written (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_userquota (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_written (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_dataset(zfs_handle_t *zhp, list_cbdata_t *cb)
{
	zprop_list_t *pl = cb->cb_proplist;
	boolean_t first = B_TRUE;
	char property[ZFS_MAXPROPLEN];
	nvlist_t *userprops = zfs_get_user_props(zhp);
	nvlist_t *propval;
	char *propstr;
	boolean_t right_justify;

	for (; pl != NULL; pl = pl->pl_next) {
		if (!first) {
			if (cb->cb_scripted)
				(void) printf("\t");
			else
				(void) printf("  ");
		} else {
			first = B_FALSE;
		}

		if (pl->pl_prop == ZFS_PROP_NAME) {
			(void) strlcpy(property, zfs_get_name(zhp),
			    sizeof (property));
			propstr = property;
			right_justify = zfs_prop_align_right(pl->pl_prop);
		} else if (pl->pl_prop != ZPROP_INVAL) {
			if (zfs_prop_get(zhp, pl->pl_prop, property,
			    sizeof (property), NULL, NULL, 0,
			    cb->cb_literal) != 0)
				propstr = "-";
			else
				propstr = property;
			right_justify = zfs_prop_align_right(pl->pl_prop);
		} else if (zfs_prop_userquota(pl->pl_user_prop)) {
			if (zfs_prop_get_userquota(zhp, pl->pl_user_prop,
			    property, sizeof (property), cb->cb_literal) != 0)
				propstr = "-";
			else
				propstr = property;
			right_justify = B_TRUE;
		} else if (zfs_prop_written(pl->pl_user_prop)) {
			if (zfs_prop_get_written(zhp, pl->pl_user_prop,
			    property, sizeof (property), cb->cb_literal) != 0)
				propstr = "-";
			else
				propstr = property;
			right_justify = B_TRUE;
		} else {
			if (nvlist_lookup_nvlist(userprops,
			    pl->pl_user_prop, &propval) != 0)
				propstr = "-";
			else
				verify(nvlist_lookup_string(propval,
				    ZPROP_VALUE, &propstr) == 0);
			right_justify = B_FALSE;
		}

		/*
		 * If this is being called in scripted mode, or if this is the
		 * last column and it is left-justified, don't include a width
		 * format specifier.
		 */
		if (cb->cb_scripted || (pl->pl_next == NULL && !right_justify))
			(void) printf("%s", propstr);
		else if (right_justify)
			(void) printf("%*s", pl->pl_width, propstr);
		else
			(void) printf("%-*s", pl->pl_width, propstr);
	}

	(void) printf("\n");
}