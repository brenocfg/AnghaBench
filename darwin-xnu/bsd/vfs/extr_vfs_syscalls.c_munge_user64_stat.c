#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct user64_stat {int /*<<< orphan*/ * st_qspare; int /*<<< orphan*/  st_lspare; int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_ctimensec; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtimensec; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atimensec; int /*<<< orphan*/  st_atime; TYPE_5__ st_ctimespec; TYPE_3__ st_mtimespec; TYPE_1__ st_atimespec; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct stat {int /*<<< orphan*/ * st_qspare; int /*<<< orphan*/  st_lspare; int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_ctimensec; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtimensec; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atimensec; int /*<<< orphan*/  st_atime; TYPE_6__ st_ctimespec; TYPE_4__ st_mtimespec; TYPE_2__ st_atimespec; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct user64_stat*,int) ; 

void munge_user64_stat(struct stat *sbp, struct user64_stat *usbp)
{
	bzero(usbp, sizeof(*usbp));

	usbp->st_dev = sbp->st_dev;
	usbp->st_ino = sbp->st_ino;
	usbp->st_mode = sbp->st_mode;
	usbp->st_nlink = sbp->st_nlink;
	usbp->st_uid = sbp->st_uid;
	usbp->st_gid = sbp->st_gid;
	usbp->st_rdev = sbp->st_rdev;
#ifndef _POSIX_C_SOURCE
	usbp->st_atimespec.tv_sec = sbp->st_atimespec.tv_sec;
	usbp->st_atimespec.tv_nsec = sbp->st_atimespec.tv_nsec;
	usbp->st_mtimespec.tv_sec = sbp->st_mtimespec.tv_sec;
	usbp->st_mtimespec.tv_nsec = sbp->st_mtimespec.tv_nsec;
	usbp->st_ctimespec.tv_sec = sbp->st_ctimespec.tv_sec;
	usbp->st_ctimespec.tv_nsec = sbp->st_ctimespec.tv_nsec;
#else
	usbp->st_atime = sbp->st_atime;
	usbp->st_atimensec = sbp->st_atimensec;
	usbp->st_mtime = sbp->st_mtime;
	usbp->st_mtimensec = sbp->st_mtimensec;
	usbp->st_ctime = sbp->st_ctime;
	usbp->st_ctimensec = sbp->st_ctimensec;
#endif
	usbp->st_size = sbp->st_size;
	usbp->st_blocks = sbp->st_blocks;
	usbp->st_blksize = sbp->st_blksize;
	usbp->st_flags = sbp->st_flags;
	usbp->st_gen = sbp->st_gen;
	usbp->st_lspare = sbp->st_lspare;
	usbp->st_qspare[0] = sbp->st_qspare[0];
	usbp->st_qspare[1] = sbp->st_qspare[1];
}