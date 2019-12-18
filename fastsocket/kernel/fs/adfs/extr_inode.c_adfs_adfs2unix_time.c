#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {unsigned int tv_sec; unsigned int tv_nsec; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ stamped; int loadaddr; unsigned int execaddr; } ;

/* Variables and functions */
 TYPE_1__* ADFS_I (struct inode*) ; 
 struct timespec CURRENT_TIME_SEC ; 

__attribute__((used)) static void
adfs_adfs2unix_time(struct timespec *tv, struct inode *inode)
{
	unsigned int high, low;

	if (ADFS_I(inode)->stamped == 0)
		goto cur_time;

	high = ADFS_I(inode)->loadaddr << 24;
	low  = ADFS_I(inode)->execaddr;

	high |= low >> 8;
	low  &= 255;

	/* Files dated pre  01 Jan 1970 00:00:00. */
	if (high < 0x336e996a)
		goto too_early;

	/* Files dated post 18 Jan 2038 03:14:05. */
	if (high >= 0x656e9969)
		goto too_late;

	/* discard 2208988800 (0x336e996a00) seconds of time */
	high -= 0x336e996a;

	/* convert 40-bit centi-seconds to 32-bit seconds */
	tv->tv_sec = (((high % 100) << 8) + low) / 100 + (high / 100 << 8);
	tv->tv_nsec = 0;
	return;

 cur_time:
	*tv = CURRENT_TIME_SEC;
	return;

 too_early:
	tv->tv_sec = tv->tv_nsec = 0;
	return;

 too_late:
	tv->tv_sec = 0x7ffffffd;
	tv->tv_nsec = 0;
	return;
}