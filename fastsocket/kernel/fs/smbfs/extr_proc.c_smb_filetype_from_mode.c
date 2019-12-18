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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int /*<<< orphan*/  UNIX_TYPE_BLKDEV ; 
 int /*<<< orphan*/  UNIX_TYPE_CHARDEV ; 
 int /*<<< orphan*/  UNIX_TYPE_DIR ; 
 int /*<<< orphan*/  UNIX_TYPE_FIFO ; 
 int /*<<< orphan*/  UNIX_TYPE_FILE ; 
 int /*<<< orphan*/  UNIX_TYPE_SOCKET ; 
 int /*<<< orphan*/  UNIX_TYPE_SYMLINK ; 
 int /*<<< orphan*/  UNIX_TYPE_UNKNOWN ; 

__attribute__((used)) static u32 smb_filetype_from_mode(int mode)
{
	if (S_ISREG(mode))
		return UNIX_TYPE_FILE;
	if (S_ISDIR(mode))
		return UNIX_TYPE_DIR;
	if (S_ISLNK(mode))
		return UNIX_TYPE_SYMLINK;
	if (S_ISCHR(mode))
		return UNIX_TYPE_CHARDEV;
	if (S_ISBLK(mode))
		return UNIX_TYPE_BLKDEV;
	if (S_ISFIFO(mode))
		return UNIX_TYPE_FIFO;
	if (S_ISSOCK(mode))
		return UNIX_TYPE_SOCKET;
	return UNIX_TYPE_UNKNOWN;
}