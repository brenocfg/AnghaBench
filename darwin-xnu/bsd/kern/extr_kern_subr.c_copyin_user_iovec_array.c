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
typedef  int /*<<< orphan*/  user_addr_t ;
struct user_iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct user64_iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct user32_iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int UIO_USERSPACE64 ; 
 int copyin (int /*<<< orphan*/ ,struct user_iovec*,int) ; 

int copyin_user_iovec_array(user_addr_t uaddr, int spacetype, int count, struct user_iovec *dst)
{
	size_t size_of_iovec = ( spacetype == UIO_USERSPACE64 ? sizeof(struct user64_iovec) : sizeof(struct user32_iovec));
	int error;
	int i;

	// copyin to the front of "dst", without regard for putting records in the right places
	error = copyin(uaddr, dst, count * size_of_iovec);
	if (error)
		return (error);

	// now, unpack the entries in reverse order, so we don't overwrite anything
	for (i = count - 1; i >= 0; i--) {
		if (spacetype == UIO_USERSPACE64) {
			struct user64_iovec iovec = ((struct user64_iovec *)dst)[i];
			dst[i].iov_base = iovec.iov_base;
			dst[i].iov_len = iovec.iov_len;
		} else {
			struct user32_iovec iovec = ((struct user32_iovec *)dst)[i];
			dst[i].iov_base = iovec.iov_base;
			dst[i].iov_len = iovec.iov_len;			
		}
	}

	return (0);
}