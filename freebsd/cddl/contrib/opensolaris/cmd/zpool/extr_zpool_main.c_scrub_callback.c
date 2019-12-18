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
struct TYPE_2__ {scalar_t__ cb_type; int /*<<< orphan*/  cb_scrub_cmd; } ;
typedef  TYPE_1__ scrub_cbdata_t ;

/* Variables and functions */
 scalar_t__ POOL_SCAN_SCRUB ; 
 scalar_t__ POOL_STATE_UNAVAIL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_has_checkpoint (int /*<<< orphan*/ *) ; 
 int zpool_scan (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

int
scrub_callback(zpool_handle_t *zhp, void *data)
{
	scrub_cbdata_t *cb = data;
	int err;

	/*
	 * Ignore faulted pools.
	 */
	if (zpool_get_state(zhp) == POOL_STATE_UNAVAIL) {
		(void) fprintf(stderr, gettext("cannot scrub '%s': pool is "
		    "currently unavailable\n"), zpool_get_name(zhp));
		return (1);
	}

	err = zpool_scan(zhp, cb->cb_type, cb->cb_scrub_cmd);

	if (err == 0 && zpool_has_checkpoint(zhp) &&
	    cb->cb_type == POOL_SCAN_SCRUB) {
		(void) printf(gettext("warning: will not scrub state that "
		    "belongs to the checkpoint of pool '%s'\n"),
		    zpool_get_name(zhp));
	}

	return (err != 0);
}