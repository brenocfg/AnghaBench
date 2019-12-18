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
 int N_SLIP ; 
 int /*<<< orphan*/  SIOCSIFENCAP ; 
 int /*<<< orphan*/  TIOCSETD ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 

int os_set_slip(int fd)
{
	int disc, sencap;

	disc = N_SLIP;
	if (ioctl(fd, TIOCSETD, &disc) < 0)
		return -errno;

	sencap = 0;
	if (ioctl(fd, SIOCSIFENCAP, &sencap) < 0)
		return -errno;

	return 0;
}