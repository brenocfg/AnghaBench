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
 int read (int,void*,size_t) ; 

int readn(int fd, void *buf, size_t n)
{
	void *buf_start = buf;

	while (n) {
		int ret = read(fd, buf, n);

		if (ret <= 0)
			return ret;

		n -= ret;
		buf += ret;
	}

	return buf - buf_start;
}