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
struct stat64 {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_rdev; } ;

/* Variables and functions */
 int OS_TYPE_BLOCKDEV ; 
 int OS_TYPE_CHARDEV ; 
 int OS_TYPE_DIR ; 
 int OS_TYPE_FIFO ; 
 int OS_TYPE_FILE ; 
 int OS_TYPE_SOCK ; 
 int OS_TYPE_SYMLINK ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ lstat64 (char const*,struct stat64*) ; 
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 

int file_type(const char *path, int *maj, int *min)
{
 	struct stat64 buf;

	if (lstat64(path, &buf) < 0)
		return -errno;
	/*
	 * We cannot pass rdev as is because glibc and the kernel disagree
	 * about its definition.
	 */
	if (maj != NULL)
		*maj = major(buf.st_rdev);
	if (min != NULL)
		*min = minor(buf.st_rdev);

	if (S_ISDIR(buf.st_mode))
		return OS_TYPE_DIR;
	else if (S_ISLNK(buf.st_mode))
		return OS_TYPE_SYMLINK;
	else if (S_ISCHR(buf.st_mode))
		return OS_TYPE_CHARDEV;
	else if (S_ISBLK(buf.st_mode))
		return OS_TYPE_BLOCKDEV;
	else if (S_ISFIFO(buf.st_mode))
		return OS_TYPE_FIFO;
	else if (S_ISSOCK(buf.st_mode))
		return OS_TYPE_SOCK;
	else return OS_TYPE_FILE;
}