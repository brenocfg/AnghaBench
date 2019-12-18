#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
#define  EINVAL 130 
#define  ENOENT 129 
#define  ENOTSUP 128 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int lzc_get_holds (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int zfs_standard_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
zfs_get_holds(zfs_handle_t *zhp, nvlist_t **nvl)
{
	int err;
	char errbuf[1024];

	err = lzc_get_holds(zhp->zfs_name, nvl);

	if (err != 0) {
		libzfs_handle_t *hdl = zhp->zfs_hdl;

		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot get holds for '%s'"),
		    zhp->zfs_name);
		switch (err) {
		case ENOTSUP:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "pool must be upgraded"));
			err = zfs_error(hdl, EZFS_BADVERSION, errbuf);
			break;
		case EINVAL:
			err = zfs_error(hdl, EZFS_BADTYPE, errbuf);
			break;
		case ENOENT:
			err = zfs_error(hdl, EZFS_NOENT, errbuf);
			break;
		default:
			err = zfs_standard_error_fmt(hdl, errno, errbuf);
			break;
		}
	}

	return (err);
}