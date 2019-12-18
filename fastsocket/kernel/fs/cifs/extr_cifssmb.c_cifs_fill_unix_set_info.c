#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct cifs_unix_set_info_args {int /*<<< orphan*/  device; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {void* Type; void* Permissions; void* DevMinor; void* DevMajor; void* Gid; void* Uid; void* LastModificationTime; void* LastAccessTime; void* LastStatusChange; void* NumOfBytes; void* EndOfFile; } ;
typedef  TYPE_1__ FILE_UNIX_BASIC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_CHANGE_64 ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIX_BLOCKDEV ; 
 int /*<<< orphan*/  UNIX_CHARDEV ; 
 int /*<<< orphan*/  UNIX_DIR ; 
 int /*<<< orphan*/  UNIX_FIFO ; 
 int /*<<< orphan*/  UNIX_FILE ; 
 int /*<<< orphan*/  UNIX_SOCKET ; 
 int /*<<< orphan*/  UNIX_SYMLINK ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_fill_unix_set_info(FILE_UNIX_BASIC_INFO *data_offset,
			const struct cifs_unix_set_info_args *args)
{
	u64 mode = args->mode;

	/*
	 * Samba server ignores set of file size to zero due to bugs in some
	 * older clients, but we should be precise - we use SetFileSize to
	 * set file size and do not want to truncate file size to zero
	 * accidently as happened on one Samba server beta by putting
	 * zero instead of -1 here
	 */
	data_offset->EndOfFile = cpu_to_le64(NO_CHANGE_64);
	data_offset->NumOfBytes = cpu_to_le64(NO_CHANGE_64);
	data_offset->LastStatusChange = cpu_to_le64(args->ctime);
	data_offset->LastAccessTime = cpu_to_le64(args->atime);
	data_offset->LastModificationTime = cpu_to_le64(args->mtime);
	data_offset->Uid = cpu_to_le64(args->uid);
	data_offset->Gid = cpu_to_le64(args->gid);
	/* better to leave device as zero when it is  */
	data_offset->DevMajor = cpu_to_le64(MAJOR(args->device));
	data_offset->DevMinor = cpu_to_le64(MINOR(args->device));
	data_offset->Permissions = cpu_to_le64(mode);

	if (S_ISREG(mode))
		data_offset->Type = cpu_to_le32(UNIX_FILE);
	else if (S_ISDIR(mode))
		data_offset->Type = cpu_to_le32(UNIX_DIR);
	else if (S_ISLNK(mode))
		data_offset->Type = cpu_to_le32(UNIX_SYMLINK);
	else if (S_ISCHR(mode))
		data_offset->Type = cpu_to_le32(UNIX_CHARDEV);
	else if (S_ISBLK(mode))
		data_offset->Type = cpu_to_le32(UNIX_BLOCKDEV);
	else if (S_ISFIFO(mode))
		data_offset->Type = cpu_to_le32(UNIX_FIFO);
	else if (S_ISSOCK(mode))
		data_offset->Type = cpu_to_le32(UNIX_SOCKET);
}