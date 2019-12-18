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
typedef  int u32 ;
struct pt1 {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  pt1_printk (int /*<<< orphan*/ ,struct pt1*,char*) ; 
 int pt1_read_reg (struct pt1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_write_reg (struct pt1*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static int pt1_do_enable_ram(struct pt1 *pt1)
{
	int i, j;
	u32 status;
	status = pt1_read_reg(pt1, 0) & 0x00000004;
	pt1_write_reg(pt1, 0, 0x00000002);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 1024; j++) {
			if ((pt1_read_reg(pt1, 0) & 0x00000004) != status)
				return 0;
		}
		schedule_timeout_uninterruptible((HZ + 999) / 1000);
	}
	pt1_printk(KERN_ERR, pt1, "could not enable RAM\n");
	return -EIO;
}