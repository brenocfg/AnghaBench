#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct holdarg {char const* snapname; char const* tag; int error; int /*<<< orphan*/ * nvl; int /*<<< orphan*/  recursive; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  EINVAL 130 
#define  ENOTSUP 129 
#define  ESRCH 128 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_REFTAG_RELE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int fnvpair_value_int32 (int /*<<< orphan*/ *) ; 
 int lzc_release (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfs_handle_dup (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_release_one (int /*<<< orphan*/ ,struct holdarg*) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  zfs_standard_error_fmt (int /*<<< orphan*/ *,int,char*) ; 

int
zfs_release(zfs_handle_t *zhp, const char *snapname, const char *tag,
    boolean_t recursive)
{
	int ret;
	struct holdarg ha;
	nvlist_t *errors = NULL;
	nvpair_t *elem;
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	char errbuf[1024];

	ha.nvl = fnvlist_alloc();
	ha.snapname = snapname;
	ha.tag = tag;
	ha.recursive = recursive;
	ha.error = 0;
	(void) zfs_release_one(zfs_handle_dup(zhp), &ha);

	if (nvlist_empty(ha.nvl)) {
		fnvlist_free(ha.nvl);
		ret = ha.error;
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN,
		    "cannot release hold from snapshot '%s@%s'"),
		    zhp->zfs_name, snapname);
		if (ret == ESRCH) {
			(void) zfs_error(hdl, EZFS_REFTAG_RELE, errbuf);
		} else {
			(void) zfs_standard_error(hdl, ret, errbuf);
		}
		return (ret);
	}

	ret = lzc_release(ha.nvl, &errors);
	fnvlist_free(ha.nvl);

	if (ret == 0) {
		/* There may be errors even in the success case. */
		fnvlist_free(errors);
		return (0);
	}

	if (nvlist_empty(errors)) {
		/* no hold-specific errors */
		(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
		    "cannot release"));
		switch (errno) {
		case ENOTSUP:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "pool must be upgraded"));
			(void) zfs_error(hdl, EZFS_BADVERSION, errbuf);
			break;
		default:
			(void) zfs_standard_error_fmt(hdl, errno, errbuf);
		}
	}

	for (elem = nvlist_next_nvpair(errors, NULL);
	    elem != NULL;
	    elem = nvlist_next_nvpair(errors, elem)) {
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN,
		    "cannot release hold from snapshot '%s'"),
		    nvpair_name(elem));
		switch (fnvpair_value_int32(elem)) {
		case ESRCH:
			(void) zfs_error(hdl, EZFS_REFTAG_RELE, errbuf);
			break;
		case EINVAL:
			(void) zfs_error(hdl, EZFS_BADTYPE, errbuf);
			break;
		default:
			(void) zfs_standard_error_fmt(hdl,
			    fnvpair_value_int32(elem), errbuf);
		}
	}

	fnvlist_free(errors);
	return (ret);
}