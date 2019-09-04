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
typedef  struct uio* uio_t ;
typedef  int u_int ;
struct user_msghdr_x {scalar_t__ msg_datalen; int /*<<< orphan*/  msg_flags; } ;
struct user64_msghdr_x {scalar_t__ msg_datalen; int /*<<< orphan*/  msg_flags; } ;
struct user32_msghdr_x {scalar_t__ msg_datalen; int /*<<< orphan*/  msg_flags; } ;
struct uio {int dummy; } ;

/* Variables and functions */
 int UIO_USERSPACE64 ; 
 scalar_t__ uio_resid (struct uio*) ; 

u_int
externalize_user_msghdr_array(void *dst, int spacetype, int direction,
    u_int count, const struct user_msghdr_x *src, struct uio **uiop)
{
#pragma unused(direction)
	u_int i;
	int seenlast = 0;
	u_int retcnt = 0;

	for (i = 0; i < count; i++) {
		const struct user_msghdr_x *user_msg = src + i;
		uio_t auio = uiop[i];
		user_ssize_t len = user_msg->msg_datalen - uio_resid(auio);

		if (user_msg->msg_datalen != 0 && len == 0)
			seenlast = 1;

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