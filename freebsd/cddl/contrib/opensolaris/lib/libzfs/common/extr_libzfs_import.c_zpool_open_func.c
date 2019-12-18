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
struct stat64 {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rn_config; int /*<<< orphan*/  rn_hdl; int /*<<< orphan*/  rn_name; int /*<<< orphan*/  rn_avl; int /*<<< orphan*/  rn_dfd; scalar_t__ rn_nozpool; } ;
typedef  TYPE_1__ rdsk_node_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ SPA_MINDEVSIZE ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_slices (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat64 (int,struct stat64*) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nozpool_all_slices (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int openat64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_read_label (int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
zpool_open_func(void *arg)
{
	rdsk_node_t *rn = arg;
	struct stat64 statbuf;
	nvlist_t *config;
	int fd;

	if (rn->rn_nozpool)
		return;
	if ((fd = openat64(rn->rn_dfd, rn->rn_name, O_RDONLY)) < 0) {
		/* symlink to a device that's no longer there */
		if (errno == ENOENT)
			nozpool_all_slices(rn->rn_avl, rn->rn_name);
		return;
	}
	/*
	 * Ignore failed stats.  We only want regular
	 * files, character devs and block devs.
	 */
	if (fstat64(fd, &statbuf) != 0 ||
	    (!S_ISREG(statbuf.st_mode) &&
	    !S_ISCHR(statbuf.st_mode) &&
	    !S_ISBLK(statbuf.st_mode))) {
		(void) close(fd);
		return;
	}
	/* this file is too small to hold a zpool */
#ifdef illumos
	if (S_ISREG(statbuf.st_mode) &&
	    statbuf.st_size < SPA_MINDEVSIZE) {
		(void) close(fd);
		return;
	} else if (!S_ISREG(statbuf.st_mode)) {
		/*
		 * Try to read the disk label first so we don't have to
		 * open a bunch of minor nodes that can't have a zpool.
		 */
		check_slices(rn->rn_avl, fd, rn->rn_name);
	}
#else	/* !illumos */
	if (statbuf.st_size < SPA_MINDEVSIZE) {
		(void) close(fd);
		return;
	}
#endif	/* illumos */

	if ((zpool_read_label(fd, &config)) != 0 && errno == ENOMEM) {
		(void) close(fd);
		(void) no_memory(rn->rn_hdl);
		return;
	}
	(void) close(fd);

	rn->rn_config = config;
}