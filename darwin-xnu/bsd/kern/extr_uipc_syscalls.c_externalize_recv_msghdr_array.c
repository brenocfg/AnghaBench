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
typedef  scalar_t__ user_ssize_t ;
typedef  scalar_t__ u_int ;
struct user_msghdr_x {scalar_t__ msg_datalen; int /*<<< orphan*/  msg_flags; } ;
struct user64_msghdr_x {scalar_t__ msg_datalen; int /*<<< orphan*/  msg_flags; } ;
struct user32_msghdr_x {scalar_t__ msg_datalen; int /*<<< orphan*/  msg_flags; } ;
struct recv_msg_elem {int which; int /*<<< orphan*/  uio; } ;

/* Variables and functions */
 int SOCK_MSG_DATA ; 
 int UIO_READ ; 
 int UIO_USERSPACE64 ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 

u_int
externalize_recv_msghdr_array(void *dst, int spacetype, int direction,
    u_int count, const struct user_msghdr_x *src,
    struct recv_msg_elem *recv_msg_array)
{
	u_int i;
	int seenlast = 0;
	u_int retcnt = 0;

	for (i = 0; i < count; i++) {
		const struct user_msghdr_x *user_msg = src + i;
		struct recv_msg_elem *recv_msg_elem = recv_msg_array + i;
		user_ssize_t len;

		len = user_msg->msg_datalen - uio_resid(recv_msg_elem->uio);

		if (direction == UIO_READ) {
			if ((recv_msg_elem->which & SOCK_MSG_DATA) == 0)
				seenlast = 1;
		} else {
			if (user_msg->msg_datalen != 0 && len == 0)
				seenlast = 1;
		}

		if (seenlast == 0)
			retcnt ++;

		if (spacetype == UIO_USERSPACE64) {
			struct user64_msghdr_x *msghdr64;

			msghdr64 = ((struct user64_msghdr_x *)dst) + i;

			msghdr64->msg_flags = user_msg->msg_flags;
			msghdr64->msg_datalen = len;

		} else {
			struct user32_msghdr_x *msghdr32;

			msghdr32 = ((struct user32_msghdr_x *)dst) + i;

			msghdr32->msg_flags = user_msg->msg_flags;
			msghdr32->msg_datalen = len;
		}
	}
	return (retcnt);
}