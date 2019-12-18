#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {char* cb_target; int cb_error; scalar_t__ cb_first; scalar_t__ cb_recurse; } ;
typedef  TYPE_1__ rollback_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rollback_check_dependent(zfs_handle_t *zhp, void *data)
{
	rollback_cbdata_t *cbp = data;

	if (cbp->cb_first && cbp->cb_recurse) {
		(void) fprintf(stderr, gettext("cannot rollback to "
		    "'%s': clones of previous snapshots exist\n"),
		    cbp->cb_target);
		(void) fprintf(stderr, gettext("use '-R' to "
		    "force deletion of the following clones and "
		    "dependents:\n"));
		cbp->cb_first = 0;
		cbp->cb_error = 1;
	}

	(void) fprintf(stderr, "%s\n", zfs_get_name(zhp));

	zfs_close(zhp);
	return (0);
}