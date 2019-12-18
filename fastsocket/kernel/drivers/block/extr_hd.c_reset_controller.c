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
struct TYPE_2__ {int ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  HD_CMD ; 
 int /*<<< orphan*/  HD_ERROR ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ drive_busy () ; 
 int hd_error ; 
 TYPE_1__* hd_info ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void reset_controller(void)
{
	int	i;

	outb_p(4, HD_CMD);
	for (i = 0; i < 1000; i++) barrier();
	outb_p(hd_info[0].ctl & 0x0f, HD_CMD);
	for (i = 0; i < 1000; i++) barrier();
	if (drive_busy())
		printk("hd: controller still busy\n");
	else if ((hd_error = inb(HD_ERROR)) != 1)
		printk("hd: controller reset failed: %02x\n", hd_error);
}