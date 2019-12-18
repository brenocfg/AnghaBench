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
struct sep_device {int /*<<< orphan*/  in_use; } ;
struct inode {int dummy; } ;
struct file {struct sep_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_HOST_IMR_REG_ADDR ; 
 int /*<<< orphan*/  SEP_DIRVER_IRQ_NUM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sep_device*) ; 
 int /*<<< orphan*/  sep_event ; 
 int /*<<< orphan*/  sep_write_reg (struct sep_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sep_release(struct inode *inode, struct file *filp)
{
	struct sep_device *sep =  filp->private_data;
#if 0				/*!SEP_DRIVER_POLLING_MODE */
	/* close IMR */
	sep_write_reg(sep, HW_HOST_IMR_REG_ADDR, 0x7FFF);
	/* release IRQ line */
	free_irq(SEP_DIRVER_IRQ_NUM, sep);

#endif
	/* Ensure any blocked open progresses */
	clear_bit(0, &sep->in_use);
	wake_up(&sep_event);
	return 0;
}