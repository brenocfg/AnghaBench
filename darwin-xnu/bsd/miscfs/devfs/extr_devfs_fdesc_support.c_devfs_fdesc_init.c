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
typedef  int /*<<< orphan*/  devnode_t ;
typedef  int /*<<< orphan*/  devdirent_t ;
struct TYPE_2__ {int /*<<< orphan*/ * de_dnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int /*<<< orphan*/  DEV_DEVFD ; 
 int /*<<< orphan*/  M_CACHE ; 
 int /*<<< orphan*/  NFDCACHE ; 
 int /*<<< orphan*/  dev_add_entry (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_1__* dev_root ; 
 int /*<<< orphan*/  devfs_fdesc_makelinks () ; 
 int /*<<< orphan*/  fdesc_lckgrp ; 
 int /*<<< orphan*/  fdesc_mtx ; 
 int /*<<< orphan*/  fdhash ; 
 int /*<<< orphan*/  fdhashtbl ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
devfs_fdesc_init()
{
	int error = 0;
	devnode_t *rootdir = dev_root->de_dnp;
	devdirent_t *direntp;
	
	/* XXX Make sure you have the right path... */
	fdhashtbl = hashinit(NFDCACHE, M_CACHE, &fdhash);
	fdesc_lckgrp = lck_grp_alloc_init("fdesc", NULL);
	lck_mtx_init(&fdesc_mtx, fdesc_lckgrp, NULL);

	DEVFS_LOCK();
	dev_add_entry("fd", rootdir, DEV_DEVFD, NULL, NULL, NULL, &direntp);
	devfs_fdesc_makelinks();
	DEVFS_UNLOCK();

	return(error);
}