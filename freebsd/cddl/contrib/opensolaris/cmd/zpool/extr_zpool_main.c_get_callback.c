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
typedef  int /*<<< orphan*/  zprop_source_t ;
struct TYPE_4__ {scalar_t__ pl_prop; int /*<<< orphan*/  pl_user_prop; struct TYPE_4__* pl_next; } ;
typedef  TYPE_1__ zprop_list_t ;
struct TYPE_5__ {int /*<<< orphan*/  cb_literal; TYPE_1__* cb_proplist; } ;
typedef  TYPE_2__ zprop_get_cbdata_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 int MAXNAMELEN ; 
 scalar_t__ ZPOOL_PROP_NAME ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_prop (int /*<<< orphan*/ *,scalar_t__,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_prop_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_prop_get_feature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zpool_prop_to_name (scalar_t__) ; 
 scalar_t__ zpool_prop_unsupported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprop_print_one_property (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_callback(zpool_handle_t *zhp, void *data)
{
	zprop_get_cbdata_t *cbp = (zprop_get_cbdata_t *)data;
	char value[MAXNAMELEN];
	zprop_source_t srctype;
	zprop_list_t *pl;

	for (pl = cbp->cb_proplist; pl != NULL; pl = pl->pl_next) {

		/*
		 * Skip the special fake placeholder. This will also skip
		 * over the name property when 'all' is specified.
		 */
		if (pl->pl_prop == ZPOOL_PROP_NAME &&
		    pl == cbp->cb_proplist)
			continue;

		if (pl->pl_prop == ZPROP_INVAL &&
		    (zpool_prop_feature(pl->pl_user_prop) ||
		    zpool_prop_unsupported(pl->pl_user_prop))) {
			srctype = ZPROP_SRC_LOCAL;

			if (zpool_prop_get_feature(zhp, pl->pl_user_prop,
			    value, sizeof (value)) == 0) {
				zprop_print_one_property(zpool_get_name(zhp),
				    cbp, pl->pl_user_prop, value, srctype,
				    NULL, NULL);
			}
		} else {
			if (zpool_get_prop(zhp, pl->pl_prop, value,
			    sizeof (value), &srctype, cbp->cb_literal) != 0)
				continue;

			zprop_print_one_property(zpool_get_name(zhp), cbp,
			    zpool_prop_to_name(pl->pl_prop), value, srctype,
			    NULL, NULL);
		}
	}
	return (0);
}