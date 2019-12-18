#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int irq; } ;
typedef  TYPE_1__ act2000_card ;

/* Variables and functions */
 unsigned char ISA_COR_IRQ03 ; 
 unsigned char ISA_COR_IRQ05 ; 
 unsigned char ISA_COR_IRQ07 ; 
 unsigned char ISA_COR_IRQ10 ; 
 unsigned char ISA_COR_IRQ11 ; 
 unsigned char ISA_COR_IRQ12 ; 
 unsigned char ISA_COR_IRQ15 ; 
 unsigned char ISA_COR_IRQOFF ; 
 unsigned char ISA_COR_PERR ; 
 int /*<<< orphan*/  ISA_PORT_COR ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
act2000_isa_select_irq(act2000_card * card)
{
	unsigned char reg;

	reg = (inb(ISA_PORT_COR) & ~ISA_COR_IRQOFF) | ISA_COR_PERR;
	switch (card->irq) {
		case 3:
			reg = ISA_COR_IRQ03;
			break;
		case 5:
			reg = ISA_COR_IRQ05;
			break;
		case 7:
			reg = ISA_COR_IRQ07;
			break;
		case 10:
			reg = ISA_COR_IRQ10;
			break;
		case 11:
			reg = ISA_COR_IRQ11;
			break;
		case 12:
			reg = ISA_COR_IRQ12;
			break;
		case 15:
			reg = ISA_COR_IRQ15;
			break;
	}
	outb(reg, ISA_PORT_COR);
}