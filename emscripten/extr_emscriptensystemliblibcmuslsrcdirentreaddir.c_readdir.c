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
struct dirent {scalar_t__ d_reclen; int /*<<< orphan*/  d_off; } ;
struct TYPE_3__ {scalar_t__ buf_pos; scalar_t__ buf_end; scalar_t__ buf; int /*<<< orphan*/  tell; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SYS_getdents ; 
 int __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int errno ; 

struct dirent *readdir(DIR *dir)
{
	struct dirent *de;
	
	if (dir->buf_pos >= dir->buf_end) {
		int len = __syscall(SYS_getdents, dir->fd, dir->buf, sizeof dir->buf);
		if (len <= 0) {
			if (len < 0 && len != -ENOENT) errno = -len;
			return 0;
		}
		dir->buf_end = len;
		dir->buf_pos = 0;
	}
	de = (void *)(dir->buf + dir->buf_pos);
	dir->buf_pos += de->d_reclen;
	dir->tell = de->d_off;
	return de;
}