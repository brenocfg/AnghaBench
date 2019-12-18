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
struct sockaddr {int dummy; } ;
struct msghdr {int msg_iovlen; struct iovec* msg_iov; struct sockaddr* msg_name; scalar_t__ msg_namelen; } ;
struct iovec {size_t iov_len; } ;

/* Variables and functions */
 long EFAULT ; 
 long INT_MAX ; 
 int VERIFY_READ ; 
 scalar_t__ copy_from_user (struct iovec*,struct iovec*,int) ; 
 long move_addr_to_kernel (struct sockaddr*,scalar_t__,struct sockaddr*) ; 

long verify_iovec(struct msghdr *m, struct iovec *iov, struct sockaddr *address, int mode)
{
	int size, ct;
	long err;

	if (m->msg_namelen) {
		if (mode == VERIFY_READ) {
			err = move_addr_to_kernel(m->msg_name, m->msg_namelen,
						  address);
			if (err < 0)
				return err;
		}
		m->msg_name = address;
	} else {
		m->msg_name = NULL;
	}

	size = m->msg_iovlen * sizeof(struct iovec);
	if (copy_from_user(iov, m->msg_iov, size))
		return -EFAULT;

	m->msg_iov = iov;
	err = 0;

	for (ct = 0; ct < m->msg_iovlen; ct++) {
		size_t len = iov[ct].iov_len;

		if (len > INT_MAX - err) {
			len = INT_MAX - err;
			iov[ct].iov_len = len;
		}
		err += len;
	}

	return err;
}