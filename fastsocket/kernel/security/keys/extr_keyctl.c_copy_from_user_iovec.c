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
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 long EFAULT ; 
 scalar_t__ copy_from_user (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long copy_from_user_iovec(void *buffer, const struct iovec *iov,
				 unsigned ioc)
{
	for (; ioc > 0; ioc--) {
		if (copy_from_user(buffer, iov->iov_base, iov->iov_len) != 0)
			return -EFAULT;
		buffer += iov->iov_len;
		iov++;
	}
	return 0;
}