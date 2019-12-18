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
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int,int) ; 

__attribute__((used)) static void hpfs_pos_ins(loff_t *p, loff_t d, loff_t c)
{
	if ((*p & ~0x3f) == (d & ~0x3f) && (*p & 0x3f) >= (d & 0x3f)) {
		int n = (*p & 0x3f) + c;
		if (n > 0x3f) printk("HPFS: hpfs_pos_ins: %08x + %d\n", (int)*p, (int)c >> 8);
		else *p = (*p & ~0x3f) | n;
	}
}