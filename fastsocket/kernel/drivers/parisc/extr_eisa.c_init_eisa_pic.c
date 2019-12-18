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
 int /*<<< orphan*/  EISA_DBG (char*,int) ; 
 int eisa_in8 (int) ; 
 int eisa_irq_level ; 
 int /*<<< orphan*/  eisa_irq_lock ; 
 int /*<<< orphan*/  eisa_out8 (int,int) ; 
 int master_mask ; 
 int slave_mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void init_eisa_pic(void)
{
	unsigned long flags;
	
	spin_lock_irqsave(&eisa_irq_lock, flags);

	eisa_out8(0xff, 0x21); /* mask during init */
	eisa_out8(0xff, 0xa1); /* mask during init */
	
	/* master pic */
	eisa_out8(0x11,0x20); /* ICW1 */   
	eisa_out8(0x00,0x21); /* ICW2 */   
	eisa_out8(0x04,0x21); /* ICW3 */   
	eisa_out8(0x01,0x21); /* ICW4 */   
	eisa_out8(0x40,0x20); /* OCW2 */   
	
	/* slave pic */
	eisa_out8(0x11,0xa0); /* ICW1 */   
	eisa_out8(0x08,0xa1); /* ICW2 */   
        eisa_out8(0x02,0xa1); /* ICW3 */   
	eisa_out8(0x01,0xa1); /* ICW4 */   
	eisa_out8(0x40,0xa0); /* OCW2 */   
        
	udelay(100);
	
	slave_mask = 0xff; 
	master_mask = 0xfb; 
	eisa_out8(slave_mask, 0xa1); /* OCW1 */
	eisa_out8(master_mask, 0x21); /* OCW1 */
	
	/* setup trig level */
	EISA_DBG("EISA edge/level %04x\n", eisa_irq_level);
	
	eisa_out8(eisa_irq_level&0xff, 0x4d0); /* Set all irq's to edge  */
	eisa_out8((eisa_irq_level >> 8) & 0xff, 0x4d1); 
	
	EISA_DBG("pic0 mask %02x\n", eisa_in8(0x21));
	EISA_DBG("pic1 mask %02x\n", eisa_in8(0xa1));
	EISA_DBG("pic0 edge/level %02x\n", eisa_in8(0x4d0));
	EISA_DBG("pic1 edge/level %02x\n", eisa_in8(0x4d1));
	
	spin_unlock_irqrestore(&eisa_irq_lock, flags);
}