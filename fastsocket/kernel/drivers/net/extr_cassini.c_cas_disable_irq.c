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
struct cas {int cas_flags; scalar_t__ regs; } ;

/* Variables and functions */
 int CAS_FLAG_REG_PLUS ; 
 int INTRN_MASK_CLEAR_ALL ; 
 int INTRN_MASK_RX_EN ; 
 scalar_t__ REG_INTR_MASK ; 
 scalar_t__ REG_PLUS_INTRN_MASK (int const) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_disable_irq(struct cas *cp, const int ring)
{
	/* Make sure we won't get any more interrupts */
	if (ring == 0) {
		writel(0xFFFFFFFF, cp->regs + REG_INTR_MASK);
		return;
	}

	/* disable completion interrupts and selectively mask */
	if (cp->cas_flags & CAS_FLAG_REG_PLUS) {
		switch (ring) {
#if defined (USE_PCI_INTB) || defined(USE_PCI_INTC) || defined(USE_PCI_INTD)
#ifdef USE_PCI_INTB
		case 1:
#endif
#ifdef USE_PCI_INTC
		case 2:
#endif
#ifdef USE_PCI_INTD
		case 3:
#endif
			writel(INTRN_MASK_CLEAR_ALL | INTRN_MASK_RX_EN,
			       cp->regs + REG_PLUS_INTRN_MASK(ring));
			break;
#endif
		default:
			writel(INTRN_MASK_CLEAR_ALL, cp->regs +
			       REG_PLUS_INTRN_MASK(ring));
			break;
		}
	}
}