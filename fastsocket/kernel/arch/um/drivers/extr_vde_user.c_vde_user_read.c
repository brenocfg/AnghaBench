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
typedef  int /*<<< orphan*/  VDECONN ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTCONN ; 
 int errno ; 
 int vde_recv (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 

int vde_user_read(void *conn, void *buf, int len)
{
	VDECONN *vconn = conn;
	int rv;

	if (vconn == NULL)
		return 0;

	rv = vde_recv(vconn, buf, len, 0);
	if (rv < 0) {
		if (errno == EAGAIN)
			return 0;
		return -errno;
	}
	else if (rv == 0)
		return -ENOTCONN;

	return rv;
}