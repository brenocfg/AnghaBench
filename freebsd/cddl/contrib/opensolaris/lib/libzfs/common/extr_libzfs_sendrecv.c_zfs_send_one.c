#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ dryrun; int /*<<< orphan*/  parsable; scalar_t__ verbose; scalar_t__ compress; scalar_t__ embed_data; scalar_t__ largeblock; } ;
typedef  TYPE_2__ sendflags_t ;
typedef  char* longlong_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  EBUSY 142 
#define  EDQUOT 141 
#define  EFAULT 140 
#define  EFBIG 139 
#define  EIO 138 
#define  ENOENT 137 
#define  ENOLINK 136 
#define  ENOSPC 135 
#define  ENOSTR 134 
#define  ENXIO 133 
#define  EPIPE 132 
#define  ERANGE 131 
#define  EROFS 130 
#define  ESRCH 129 
#define  EXDEV 128 
 int /*<<< orphan*/  EZFS_BADBACKUP ; 
 int /*<<< orphan*/  EZFS_BUSY ; 
 int /*<<< orphan*/  EZFS_CROSSTARGET ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int LZC_SEND_FLAG_COMPRESS ; 
 int LZC_SEND_FLAG_EMBED_DATA ; 
 int LZC_SEND_FLAG_LARGE_BLOCK ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lzc_exists (int /*<<< orphan*/ ) ; 
 int lzc_send (int /*<<< orphan*/ ,char const*,int,int) ; 
 int lzc_send_space (int /*<<< orphan*/ ,char const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  send_print_verbose (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 char* strerror (int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  zfs_nicenum (scalar_t__,char*,int) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zfs_send_one(zfs_handle_t *zhp, const char *from, int fd, sendflags_t flags)
{
	int err = 0;
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	enum lzc_send_flags lzc_flags = 0;
	FILE *fout = (flags.verbose && flags.dryrun) ? stdout : stderr;
	char errbuf[1024];

	if (flags.largeblock)
		lzc_flags |= LZC_SEND_FLAG_LARGE_BLOCK;
	if (flags.embed_data)
		lzc_flags |= LZC_SEND_FLAG_EMBED_DATA;
	if (flags.compress)
		lzc_flags |= LZC_SEND_FLAG_COMPRESS;

	if (flags.verbose) {
		uint64_t size = 0;
		err = lzc_send_space(zhp->zfs_name, from, lzc_flags, &size);
		if (err == 0) {
			send_print_verbose(fout, zhp->zfs_name, from, size,
			    flags.parsable);
			if (flags.parsable) {
				(void) fprintf(fout, "size\t%llu\n",
				    (longlong_t)size);
			} else {
				char buf[16];
				zfs_nicenum(size, buf, sizeof (buf));
				(void) fprintf(fout, dgettext(TEXT_DOMAIN,
				    "total estimated size is %s\n"), buf);
			}
		} else {
			(void) fprintf(stderr, "Cannot estimate send size: "
			    "%s\n", strerror(errno));
		}
	}

	if (flags.dryrun)
		return (err);

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "warning: cannot send '%s'"), zhp->zfs_name);

	err = lzc_send(zhp->zfs_name, from, fd, lzc_flags);
	if (err != 0) {
		switch (errno) {
		case EXDEV:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "not an earlier snapshot from the same fs"));
			return (zfs_error(hdl, EZFS_CROSSTARGET, errbuf));

		case ENOENT:
		case ESRCH:
			if (lzc_exists(zhp->zfs_name)) {
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "incremental source (%s) does not exist"),
				    from);
			}
			return (zfs_error(hdl, EZFS_NOENT, errbuf));

		case EBUSY:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "target is busy; if a filesystem, "
			    "it must not be mounted"));
			return (zfs_error(hdl, EZFS_BUSY, errbuf));

		case EDQUOT:
		case EFBIG:
		case EIO:
		case ENOLINK:
		case ENOSPC:
#ifdef illumos
		case ENOSTR:
#endif
		case ENXIO:
		case EPIPE:
		case ERANGE:
		case EFAULT:
		case EROFS:
			zfs_error_aux(hdl, strerror(errno));
			return (zfs_error(hdl, EZFS_BADBACKUP, errbuf));

		default:
			return (zfs_standard_error(hdl, errno, errbuf));
		}
	}
	return (err != 0);
}