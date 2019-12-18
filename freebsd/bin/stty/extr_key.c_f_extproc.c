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
struct info {int /*<<< orphan*/  fd; scalar_t__ off; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCEXT ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
f_extproc(struct info *ip)
{

	if (ip->off) {
		int tmp = 0;
		(void)ioctl(ip->fd, TIOCEXT, &tmp);
	} else {
		int tmp = 1;
		(void)ioctl(ip->fd, TIOCEXT, &tmp);
	}
}