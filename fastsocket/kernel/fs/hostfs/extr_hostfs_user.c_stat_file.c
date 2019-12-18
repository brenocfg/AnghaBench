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
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct stat64 {unsigned long long st_ino; int st_mode; int st_nlink; int st_uid; int st_gid; unsigned long long st_size; int st_blksize; unsigned long long st_blocks; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;

/* Variables and functions */
 int errno ; 
 scalar_t__ fstat64 (int,struct stat64*) ; 
 scalar_t__ lstat64 (char const*,struct stat64*) ; 

int stat_file(const char *path, unsigned long long *inode_out, int *mode_out,
	      int *nlink_out, int *uid_out, int *gid_out,
	      unsigned long long *size_out, struct timespec *atime_out,
	      struct timespec *mtime_out, struct timespec *ctime_out,
	      int *blksize_out, unsigned long long *blocks_out, int fd)
{
	struct stat64 buf;

	if (fd >= 0) {
		if (fstat64(fd, &buf) < 0)
			return -errno;
	} else if (lstat64(path, &buf) < 0) {
		return -errno;
	}

	if (inode_out != NULL)
		*inode_out = buf.st_ino;
	if (mode_out != NULL)
		*mode_out = buf.st_mode;
	if (nlink_out != NULL)
		*nlink_out = buf.st_nlink;
	if (uid_out != NULL)
		*uid_out = buf.st_uid;
	if (gid_out != NULL)
		*gid_out = buf.st_gid;
	if (size_out != NULL)
		*size_out = buf.st_size;
	if (atime_out != NULL) {
		atime_out->tv_sec = buf.st_atime;
		atime_out->tv_nsec = 0;
	}
	if (mtime_out != NULL) {
		mtime_out->tv_sec = buf.st_mtime;
		mtime_out->tv_nsec = 0;
	}
	if (ctime_out != NULL) {
		ctime_out->tv_sec = buf.st_ctime;
		ctime_out->tv_nsec = 0;
	}
	if (blksize_out != NULL)
		*blksize_out = buf.st_blksize;
	if (blocks_out != NULL)
		*blocks_out = buf.st_blocks;
	return 0;
}