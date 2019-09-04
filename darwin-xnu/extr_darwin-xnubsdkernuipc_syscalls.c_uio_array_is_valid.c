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
typedef  size_t u_int ;
struct uio {int dummy; } ;

/* Variables and functions */
 scalar_t__ sb_max ; 
 scalar_t__ uio_resid (struct uio*) ; 

int
uio_array_is_valid(struct uio **uiop, u_int count)
{
	user_ssize_t len = 0;
	u_int i;

	for (i = 0; i < count; i++) {
		struct uio *auio = uiop[i];

		if (auio != NULL) {
			user_ssize_t resid = uio_resid(auio);

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