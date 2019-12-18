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
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  cb_unavail; scalar_t__ cb_first; } ;
typedef  TYPE_1__ upgrade_cbdata_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ POOL_STATE_UNAVAIL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
upgrade_list_unavail(zpool_handle_t *zhp, void *arg)
{
	upgrade_cbdata_t *cbp = arg;

	if (zpool_get_state(zhp) == POOL_STATE_UNAVAIL) {
		if (cbp->cb_first) {
			(void) fprintf(stderr, gettext("The following pools "
			    "are unavailable and cannot be upgraded as this "
			    "time.\n\n"));
			(void) fprintf(stderr, gettext("POOL\n"));
			(void) fprintf(stderr, gettext("------------\n"));
			cbp->cb_first = B_FALSE;
		}
		(void) printf(gettext("%s\n"), zpool_get_name(zhp));
		cbp->cb_unavail = B_TRUE;
	}
	return (0);
}