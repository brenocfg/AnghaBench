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
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
#define  E2BIG 140 
#define  EBUSY 139 
#define  EDOM 138 
#define  EINVAL 137 
#define  ENOSPC 136 
#define  ENOTSUP 135 
#define  EOVERFLOW 134 
#define  ERANGE 133 
#define  EROFS 132 
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_DSREADONLY ; 
 int /*<<< orphan*/  EZFS_NOTSUP ; 
 int /*<<< orphan*/  EZFS_PROPSPACE ; 
 int /*<<< orphan*/  EZFS_VOLTOOBIG ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_PROP_CHECKSUM ; 
 int /*<<< orphan*/  ZFS_PROP_COMPRESSION ; 
 int /*<<< orphan*/  ZFS_PROP_DEDUP ; 
#define  ZFS_PROP_QUOTA 131 
 int /*<<< orphan*/  ZFS_PROP_RECORDSIZE ; 
#define  ZFS_PROP_REFQUOTA 130 
#define  ZFS_PROP_REFRESERVATION 129 
#define  ZFS_PROP_RESERVATION 128 
 int /*<<< orphan*/  ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  ZPROP_INVAL ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_standard_error (int /*<<< orphan*/ *,int const,char*) ; 

void
zfs_setprop_error(libzfs_handle_t *hdl, zfs_prop_t prop, int err,
    char *errbuf)
{
	switch (err) {

	case ENOSPC:
		/*
		 * For quotas and reservations, ENOSPC indicates
		 * something different; setting a quota or reservation
		 * doesn't use any disk space.
		 */
		switch (prop) {
		case ZFS_PROP_QUOTA:
		case ZFS_PROP_REFQUOTA:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "size is less than current used or "
			    "reserved space"));
			(void) zfs_error(hdl, EZFS_PROPSPACE, errbuf);
			break;

		case ZFS_PROP_RESERVATION:
		case ZFS_PROP_REFRESERVATION:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "size is greater than available space"));
			(void) zfs_error(hdl, EZFS_PROPSPACE, errbuf);
			break;

		default:
			(void) zfs_standard_error(hdl, err, errbuf);
			break;
		}
		break;

	case EBUSY:
		(void) zfs_standard_error(hdl, EBUSY, errbuf);
		break;

	case EROFS:
		(void) zfs_error(hdl, EZFS_DSREADONLY, errbuf);
		break;

	case E2BIG:
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "property value too long"));
		(void) zfs_error(hdl, EZFS_BADPROP, errbuf);
		break;

	case ENOTSUP:
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "pool and or dataset must be upgraded to set this "
		    "property or value"));
		(void) zfs_error(hdl, EZFS_BADVERSION, errbuf);
		break;

	case ERANGE:
	case EDOM:
		if (prop == ZFS_PROP_COMPRESSION ||
		    prop == ZFS_PROP_RECORDSIZE) {
			(void) zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "property setting is not allowed on "
			    "bootable datasets"));
			(void) zfs_error(hdl, EZFS_NOTSUP, errbuf);
		} else if (prop == ZFS_PROP_CHECKSUM ||
		    prop == ZFS_PROP_DEDUP) {
			(void) zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "property setting is not allowed on "
			    "root pools"));
			(void) zfs_error(hdl, EZFS_NOTSUP, errbuf);
		} else {
			(void) zfs_standard_error(hdl, err, errbuf);
		}
		break;

	case EINVAL:
		if (prop == ZPROP_INVAL) {
			(void) zfs_error(hdl, EZFS_BADPROP, errbuf);
		} else {
			(void) zfs_standard_error(hdl, err, errbuf);
		}
		break;

	case EOVERFLOW:
		/*
		 * This platform can't address a volume this big.
		 */
#ifdef _ILP32
		if (prop == ZFS_PROP_VOLSIZE) {
			(void) zfs_error(hdl, EZFS_VOLTOOBIG, errbuf);
			break;
		}
#endif
		/* FALLTHROUGH */
	default:
		(void) zfs_standard_error(hdl, err, errbuf);
	}
}