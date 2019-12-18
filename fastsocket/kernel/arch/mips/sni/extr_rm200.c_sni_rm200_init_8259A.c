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
 unsigned int MASTER_ICW4_DEFAULT ; 
 unsigned int PIC_CASCADE_IR ; 
 scalar_t__ PIC_CMD ; 
 scalar_t__ PIC_IMR ; 
 unsigned int SLAVE_ICW4_DEFAULT ; 
 unsigned int cached_master_mask ; 
 unsigned int cached_slave_mask ; 
 scalar_t__ rm200_pic_master ; 
 scalar_t__ rm200_pic_slave ; 
 int /*<<< orphan*/  sni_rm200_i8259A_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

void sni_rm200_init_8259A(void)
{
	unsigned long flags;

	spin_lock_irqsave(&sni_rm200_i8259A_lock, flags);

	writeb(0xff, rm200_pic_master + PIC_IMR);
	writeb(0xff, rm200_pic_slave + PIC_IMR);

	writeb(0x11, rm200_pic_master + PIC_CMD);
	writeb(0, rm200_pic_master + PIC_IMR);
	writeb(1U << PIC_CASCADE_IR, rm200_pic_master + PIC_IMR);
	writeb(MASTER_ICW4_DEFAULT, rm200_pic_master + PIC_IMR);
	writeb(0x11, rm200_pic_slave + PIC_CMD);
	writeb(8, rm200_pic_slave + PIC_IMR);
	writeb(PIC_CASCADE_IR, rm200_pic_slave + PIC_IMR);
	writeb(SLAVE_ICW4_DEFAULT, rm200_pic_slave + PIC_IMR);
	udelay(100);		/* wait for 8259A to initialize */

	writeb(cached_master_mask, rm200_pic_master + PIC_IMR);
	writeb(cached_slave_mask, rm200_pic_slave + PIC_IMR);

	spin_unlock_irqrestore(&sni_rm200_i8259A_lock, flags);
}