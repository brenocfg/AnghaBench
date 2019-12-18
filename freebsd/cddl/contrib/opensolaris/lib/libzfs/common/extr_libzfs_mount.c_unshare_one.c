#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zfs_share_proto_t ;
typedef  int /*<<< orphan*/ * sa_share_t ;
struct TYPE_8__ {int /*<<< orphan*/  libzfs_sharehdl; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_unshare_err; int /*<<< orphan*/  p_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EZFS_UNSHARENFSFAILED ; 
 int MAXPATHLEN ; 
 size_t PROTO_NFS ; 
 int /*<<< orphan*/  SA_INIT_ONE_SHARE_FROM_NAME ; 
 int SA_OK ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_EXPORTS_PATH ; 
 int /*<<< orphan*/  _sa_errorstr (int) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fsunshare (int /*<<< orphan*/ ,char const*) ; 
 TYPE_7__* proto_table ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  zfs_error_aux (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int zfs_error_fmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,...) ; 
 int zfs_init_libshare_arg (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int zfs_sa_disable_share (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_sa_find_share (int /*<<< orphan*/ ,char*) ; 
 char* zfs_strdup (TYPE_1__*,char const*) ; 

__attribute__((used)) static int
unshare_one(libzfs_handle_t *hdl, const char *name, const char *mountpoint,
    zfs_share_proto_t proto)
{
#ifdef illumos
	sa_share_t share;
	int err;
	char *mntpt;

	/*
	 * Mountpoint could get trashed if libshare calls getmntany
	 * which it does during API initialization, so strdup the
	 * value.
	 */
	mntpt = zfs_strdup(hdl, mountpoint);

	/*
	 * make sure libshare initialized, initialize everything because we
	 * don't know what other unsharing may happen later. Functions up the
	 * stack are allowed to initialize instead a subset of shares at the
	 * time the set is known.
	 */
	if ((err = zfs_init_libshare_arg(hdl, SA_INIT_ONE_SHARE_FROM_NAME,
	    (void *)name)) != SA_OK) {
		free(mntpt);	/* don't need the copy anymore */
		return (zfs_error_fmt(hdl, proto_table[proto].p_unshare_err,
		    dgettext(TEXT_DOMAIN, "cannot unshare '%s': %s"),
		    name, _sa_errorstr(err)));
	}

	share = zfs_sa_find_share(hdl->libzfs_sharehdl, mntpt);
	free(mntpt);	/* don't need the copy anymore */

	if (share != NULL) {
		err = zfs_sa_disable_share(share, proto_table[proto].p_name);
		if (err != SA_OK) {
			return (zfs_error_fmt(hdl,
			    proto_table[proto].p_unshare_err,
			    dgettext(TEXT_DOMAIN, "cannot unshare '%s': %s"),
			    name, _sa_errorstr(err)));
		}
	} else {
		return (zfs_error_fmt(hdl, proto_table[proto].p_unshare_err,
		    dgettext(TEXT_DOMAIN, "cannot unshare '%s': not found"),
		    name));
	}
#else
	char buf[MAXPATHLEN];
	FILE *fp;
	int err;

	if (proto != PROTO_NFS) {
		fprintf(stderr, "No SMB support in FreeBSD yet.\n");
		return (EOPNOTSUPP);
	}

	err = fsunshare(ZFS_EXPORTS_PATH, mountpoint);
	if (err != 0) {
		zfs_error_aux(hdl, "%s", strerror(err));
		return (zfs_error_fmt(hdl, EZFS_UNSHARENFSFAILED,
		    dgettext(TEXT_DOMAIN,
		    "cannot unshare '%s'"), name));
	}
#endif
	return (0);
}