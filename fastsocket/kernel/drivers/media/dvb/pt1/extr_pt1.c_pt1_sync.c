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
struct pt1 {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  pt1_printk (int /*<<< orphan*/ ,struct pt1*,char*) ; 
 int pt1_read_reg (struct pt1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_write_reg (struct pt1*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pt1_sync(struct pt1 *pt1)
{
	int i;
	for (i = 0; i < 57; i++) {
		if (pt1_read_reg(pt1, 0) & 0x20000000)
			return 0;
		pt1_write_reg(pt1, 0, 0x00000008);
	}
	pt1_printk(KERN_ERR, pt1, "could not sync\n");
	return -EIO;
}