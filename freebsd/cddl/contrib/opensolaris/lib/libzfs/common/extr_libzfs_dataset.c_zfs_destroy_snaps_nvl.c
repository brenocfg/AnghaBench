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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  EEXIST 128 
 int /*<<< orphan*/  EZFS_EXISTS ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int fnvpair_value_int32 (int /*<<< orphan*/ *) ; 
 int lzc_destroy_snaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zfs_destroy_snaps_nvl(libzfs_handle_t *hdl, nvlist_t *snaps, boolean_t defer)
{
	int ret;
	nvlist_t *errlist = NULL;

	ret = lzc_destroy_snaps(snaps, defer, &errlist);

	if (ret == 0) {
		nvlist_free(errlist);
		return (0);
	}

	if (nvlist_empty(errlist)) {
		char errbuf[1024];
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot destroy snapshots"));

		ret = zfs_standard_error(hdl, ret, errbuf);
	}
	for (nvpair_t *pair = nvlist_next_nvpair(errlist, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(errlist, pair)) {
		char errbuf[1024];
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot destroy snapshot %s"),
		    nvpair_name(pair));

		switch (fnvpair_value_int32(pair)) {
		case EEXIST:
			zfs_error_aux(hdl,
			    dgettext(TEXT_DOMAIN, "snapshot is cloned"));
			ret = zfs_error(hdl, EZFS_EXISTS, errbuf);
			break;
		default:
			ret = zfs_standard_error(hdl, errno, errbuf);
			break;
		}
	}

	nvlist_free(errlist);
	return (ret);
}