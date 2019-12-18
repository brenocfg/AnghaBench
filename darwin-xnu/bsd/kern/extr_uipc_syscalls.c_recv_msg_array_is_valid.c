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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int ;
struct recv_msg_elem {int /*<<< orphan*/ * uio; } ;

/* Variables and functions */
 scalar_t__ sb_max ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ *) ; 

int
recv_msg_array_is_valid(struct recv_msg_elem *recv_msg_array, u_int count)
{
	user_ssize_t len = 0;
	u_int i;

	for (i = 0; i < count; i++) {
		struct recv_msg_elem *recv_msg_elem = recv_msg_array + i;

		if (recv_msg_elem->uio != NULL) {
			user_ssize_t resid = uio_resid(recv_msg_elem->uio);

			/*
			 * Sanity check on the validity of the iovec:
			 * no point of going over sb_max
			 */
			if (resid < 0 || (u_int32_t)resid > sb_max)
				return (0);

			len += resid;
			if (len < 0 || (u_int32_t)len > sb_max)
				return (0);
		}
	}
	return (1);
}