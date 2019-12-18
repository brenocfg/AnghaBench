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

/* Variables and functions */
 int /*<<< orphan*/  cmd640_lock ; 
 int inl (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci_conf1(void)
{
	unsigned long flags;
	u32 tmp;

	spin_lock_irqsave(&cmd640_lock, flags);
	outb(0x01, 0xCFB);
	tmp = inl(0xCF8);
	outl(0x80000000, 0xCF8);
	if (inl(0xCF8) == 0x80000000) {
		outl(tmp, 0xCF8);
		spin_unlock_irqrestore(&cmd640_lock, flags);
		return 1;
	}
	outl(tmp, 0xCF8);
	spin_unlock_irqrestore(&cmd640_lock, flags);
	return 0;
}