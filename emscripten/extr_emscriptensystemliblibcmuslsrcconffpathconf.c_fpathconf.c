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
typedef  int /*<<< orphan*/  values ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  FILESIZEBITS 156 
#define  NAME_MAX 155 
#define  PATH_MAX 154 
#define  PIPE_BUF 153 
#define  SYMLINK_MAX 152 
#define  _PC_2_SYMLINKS 151 
#define  _PC_ALLOC_SIZE_MIN 150 
#define  _PC_ASYNC_IO 149 
#define  _PC_CHOWN_RESTRICTED 148 
#define  _PC_FILESIZEBITS 147 
#define  _PC_LINK_MAX 146 
#define  _PC_MAX_CANON 145 
#define  _PC_MAX_INPUT 144 
#define  _PC_NAME_MAX 143 
#define  _PC_NO_TRUNC 142 
#define  _PC_PATH_MAX 141 
#define  _PC_PIPE_BUF 140 
#define  _PC_PRIO_IO 139 
#define  _PC_REC_INCR_XFER_SIZE 138 
#define  _PC_REC_MAX_XFER_SIZE 137 
#define  _PC_REC_MIN_XFER_SIZE 136 
#define  _PC_REC_XFER_ALIGN 135 
#define  _PC_SOCK_MAXBUF 134 
#define  _PC_SYMLINK_MAX 133 
#define  _PC_SYNC_IO 132 
#define  _PC_VDISABLE 131 
#define  _POSIX_LINK_MAX 130 
#define  _POSIX_MAX_CANON 129 
#define  _POSIX_MAX_INPUT 128 
 int /*<<< orphan*/  errno ; 

long fpathconf(int fd, int name)
{
	static const short values[] = {
		[_PC_LINK_MAX] = _POSIX_LINK_MAX,
		[_PC_MAX_CANON] = _POSIX_MAX_CANON,
		[_PC_MAX_INPUT] = _POSIX_MAX_INPUT,
		[_PC_NAME_MAX] = NAME_MAX,
		[_PC_PATH_MAX] = PATH_MAX,
		[_PC_PIPE_BUF] = PIPE_BUF,
		[_PC_CHOWN_RESTRICTED] = 1,
		[_PC_NO_TRUNC] = 1,
		[_PC_VDISABLE] = 0,
		[_PC_SYNC_IO] = 1,
		[_PC_ASYNC_IO] = -1,
		[_PC_PRIO_IO] = -1,
		[_PC_SOCK_MAXBUF] = -1,
		[_PC_FILESIZEBITS] = FILESIZEBITS,
		[_PC_REC_INCR_XFER_SIZE] = 4096,
		[_PC_REC_MAX_XFER_SIZE] = 4096,
		[_PC_REC_MIN_XFER_SIZE] = 4096,
		[_PC_REC_XFER_ALIGN] = 4096,
		[_PC_ALLOC_SIZE_MIN] = 4096,
		[_PC_SYMLINK_MAX] = SYMLINK_MAX,
		[_PC_2_SYMLINKS] = 1
	};
	if (name >= sizeof(values)/sizeof(values[0])) {
		errno = EINVAL;
		return -1;
	}
	return values[name];
}