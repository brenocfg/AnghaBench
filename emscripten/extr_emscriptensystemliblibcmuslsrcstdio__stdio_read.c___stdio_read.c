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
struct iovec {unsigned char* iov_base; size_t iov_len; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {size_t buf_size; unsigned char* buf; size_t flags; unsigned char* rpos; unsigned char* rend; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 size_t F_EOF ; 
 size_t F_ERR ; 
 int /*<<< orphan*/  SYS_readv ; 
 size_t syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*,int) ; 

size_t __stdio_read(FILE *f, unsigned char *buf, size_t len)
{
	struct iovec iov[2] = {
		{ .iov_base = buf, .iov_len = len - !!f->buf_size },
		{ .iov_base = f->buf, .iov_len = f->buf_size }
	};
	ssize_t cnt;

	cnt = syscall(SYS_readv, f->fd, iov, 2);
	if (cnt <= 0) {
		f->flags |= F_EOF ^ ((F_ERR^F_EOF) & cnt);
		return cnt;
	}
	if (cnt <= iov[0].iov_len) return cnt;
	cnt -= iov[0].iov_len;
	f->rpos = f->buf;
	f->rend = f->buf + cnt;
	if (f->buf_size) buf[len-1] = *f->rpos++;
	return len;
}