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

/* Variables and functions */
 int EINVAL ; 
 int SHUT_RD ; 
 int SHUT_RDWR ; 
 int SHUT_WR ; 
 int errno ; 
 int shutdown (int,int) ; 

int os_shutdown_socket(int fd, int r, int w)
{
	int what, err;

	if (r && w)
		what = SHUT_RDWR;
	else if (r)
		what = SHUT_RD;
	else if (w)
		what = SHUT_WR;
	else
		return -EINVAL;

	err = shutdown(fd, what);
	if (err < 0)
		return -errno;
	return 0;
}