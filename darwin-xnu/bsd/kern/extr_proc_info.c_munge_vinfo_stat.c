#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vinfo_stat {int /*<<< orphan*/ * vst_qspare; int /*<<< orphan*/  vst_rdev; int /*<<< orphan*/  vst_gen; int /*<<< orphan*/  vst_flags; int /*<<< orphan*/  vst_blksize; int /*<<< orphan*/  vst_blocks; int /*<<< orphan*/  vst_size; int /*<<< orphan*/  vst_birthtimensec; int /*<<< orphan*/  vst_birthtime; int /*<<< orphan*/  vst_ctimensec; int /*<<< orphan*/  vst_ctime; int /*<<< orphan*/  vst_mtimensec; int /*<<< orphan*/  vst_mtime; int /*<<< orphan*/  vst_atimensec; int /*<<< orphan*/  vst_atime; int /*<<< orphan*/  vst_gid; int /*<<< orphan*/  vst_uid; int /*<<< orphan*/  vst_ino; int /*<<< orphan*/  vst_nlink; int /*<<< orphan*/  vst_mode; int /*<<< orphan*/  vst_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct stat64 {int /*<<< orphan*/ * st_qspare; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_size; TYPE_4__ st_birthtimespec; TYPE_3__ st_ctimespec; TYPE_2__ st_mtimespec; TYPE_1__ st_atimespec; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct vinfo_stat*,int) ; 

__attribute__((used)) static void
munge_vinfo_stat(struct stat64 *sbp, struct vinfo_stat *vsbp)
{
        bzero(vsbp, sizeof(struct vinfo_stat));

	vsbp->vst_dev = sbp->st_dev;
	vsbp->vst_mode = sbp->st_mode;
	vsbp->vst_nlink = sbp->st_nlink;
	vsbp->vst_ino = sbp->st_ino;
	vsbp->vst_uid = sbp->st_uid;
	vsbp->vst_gid = sbp->st_gid;
	vsbp->vst_atime = sbp->st_atimespec.tv_sec;
	vsbp->vst_atimensec = sbp->st_atimespec.tv_nsec;
	vsbp->vst_mtime = sbp->st_mtimespec.tv_sec;
	vsbp->vst_mtimensec = sbp->st_mtimespec.tv_nsec;
	vsbp->vst_ctime = sbp->st_ctimespec.tv_sec;
	vsbp->vst_ctimensec = sbp->st_ctimespec.tv_nsec;
	vsbp->vst_birthtime = sbp->st_birthtimespec.tv_sec;
	vsbp->vst_birthtimensec = sbp->st_birthtimespec.tv_nsec;
	vsbp->vst_size = sbp->st_size;
	vsbp->vst_blocks = sbp->st_blocks;
	vsbp->vst_blksize = sbp->st_blksize;
	vsbp->vst_flags = sbp->st_flags;
	vsbp->vst_gen = sbp->st_gen;
	vsbp->vst_rdev = sbp->st_rdev;
	vsbp->vst_qspare[0] = sbp->st_qspare[0];
	vsbp->vst_qspare[1] = sbp->st_qspare[1];
}