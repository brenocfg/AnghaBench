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
struct stat {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; scalar_t__ st_blksize; scalar_t__ st_size; scalar_t__ st_blocks; scalar_t__ st_rdev; scalar_t__ st_gid; scalar_t__ st_uid; scalar_t__ st_nlink; int /*<<< orphan*/  st_mode; scalar_t__ st_ino; } ;
struct fio_stat {int /*<<< orphan*/  fst_ctime; int /*<<< orphan*/  fst_mtime; int /*<<< orphan*/  fst_atime; int /*<<< orphan*/  fst_blocks; int /*<<< orphan*/  fst_blksize; int /*<<< orphan*/  fst_size; int /*<<< orphan*/  fst_rdev; int /*<<< orphan*/  fst_gid; int /*<<< orphan*/  fst_uid; int /*<<< orphan*/  fst_nlink; int /*<<< orphan*/  fst_mode; int /*<<< orphan*/  fst_ino; } ;
typedef  int LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  remote_fileio_to_fio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_uint (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_ulong (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remote_fileio_to_fio_stat (struct stat *st, struct fio_stat *fst)
{
  /* `st_dev' is set in the calling function */
  remote_fileio_to_fio_uint ((long) st->st_ino, fst->fst_ino);
  remote_fileio_to_fio_mode (st->st_mode, fst->fst_mode);
  remote_fileio_to_fio_uint ((long) st->st_nlink, fst->fst_nlink);
  remote_fileio_to_fio_uint ((long) st->st_uid, fst->fst_uid);
  remote_fileio_to_fio_uint ((long) st->st_gid, fst->fst_gid);
  remote_fileio_to_fio_uint ((long) st->st_rdev, fst->fst_rdev);
  remote_fileio_to_fio_ulong ((LONGEST) st->st_size, fst->fst_size);
  remote_fileio_to_fio_ulong ((LONGEST) st->st_blksize, fst->fst_blksize);
#if HAVE_STRUCT_STAT_ST_BLOCKS
  remote_fileio_to_fio_ulong ((LONGEST) st->st_blocks, fst->fst_blocks);
#else
  /* FIXME: This is correct for DJGPP, but other systems that don't
     have st_blocks, if any, might prefer 512 instead of st_blksize.
     (eliz, 30-12-2003)  */
  remote_fileio_to_fio_ulong (((LONGEST) st->st_size + st->st_blksize - 1)
			      / (LONGEST) st->st_blksize,
			      fst->fst_blocks);
#endif
  remote_fileio_to_fio_time (st->st_atime, fst->fst_atime);
  remote_fileio_to_fio_time (st->st_mtime, fst->fst_mtime);
  remote_fileio_to_fio_time (st->st_ctime, fst->fst_ctime);
}