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
struct inode {unsigned long long i_ino; int i_mode; int i_nlink; unsigned long long i_size; unsigned long long i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int stat_file (char*,unsigned long long*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,unsigned long long*,int) ; 

__attribute__((used)) static int read_name(struct inode *ino, char *name)
{
	/*
	 * The non-int inode fields are copied into ints by stat_file and
	 * then copied into the inode because passing the actual pointers
	 * in and having them treated as int * breaks on big-endian machines
	 */
	int err;
	int i_mode, i_nlink, i_blksize;
	unsigned long long i_size;
	unsigned long long i_ino;
	unsigned long long i_blocks;

	err = stat_file(name, &i_ino, &i_mode, &i_nlink, &ino->i_uid,
			&ino->i_gid, &i_size, &ino->i_atime, &ino->i_mtime,
			&ino->i_ctime, &i_blksize, &i_blocks, -1);
	if (err)
		return err;

	ino->i_ino = i_ino;
	ino->i_mode = i_mode;
	ino->i_nlink = i_nlink;
	ino->i_size = i_size;
	ino->i_blocks = i_blocks;
	return 0;
}