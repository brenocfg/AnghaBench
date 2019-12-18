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
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned int loadaddr; unsigned int execaddr; scalar_t__ stamped; } ;

/* Variables and functions */
 TYPE_1__* ADFS_I (struct inode*) ; 

__attribute__((used)) static void
adfs_unix2adfs_time(struct inode *inode, unsigned int secs)
{
	unsigned int high, low;

	if (ADFS_I(inode)->stamped) {
		/* convert 32-bit seconds to 40-bit centi-seconds */
		low  = (secs & 255) * 100;
		high = (secs / 256) * 100 + (low >> 8) + 0x336e996a;

		ADFS_I(inode)->loadaddr = (high >> 24) |
				(ADFS_I(inode)->loadaddr & ~0xff);
		ADFS_I(inode)->execaddr = (low & 255) | (high << 8);
	}
}