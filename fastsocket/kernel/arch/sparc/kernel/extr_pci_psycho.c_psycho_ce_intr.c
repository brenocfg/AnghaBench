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
struct pci_pbm_info {unsigned long controller_regs; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long PSYCHO_CEAFSR_BLK ; 
 unsigned long PSYCHO_CEAFSR_BMSK ; 
 unsigned long PSYCHO_CEAFSR_DOFF ; 
 unsigned long PSYCHO_CEAFSR_ESYND ; 
 unsigned long PSYCHO_CEAFSR_MID ; 
 unsigned long PSYCHO_CEAFSR_PDRD ; 
 unsigned long PSYCHO_CEAFSR_PDWR ; 
 unsigned long PSYCHO_CEAFSR_PPIO ; 
 unsigned long PSYCHO_CEAFSR_SDRD ; 
 unsigned long PSYCHO_CEAFSR_SDWR ; 
 unsigned long PSYCHO_CEAFSR_SPIO ; 
 unsigned long PSYCHO_CE_AFAR ; 
 unsigned long PSYCHO_CE_AFSR ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t psycho_ce_intr(int irq, void *dev_id)
{
	struct pci_pbm_info *pbm = dev_id;
	unsigned long afsr_reg = pbm->controller_regs + PSYCHO_CE_AFSR;
	unsigned long afar_reg = pbm->controller_regs + PSYCHO_CE_AFAR;
	unsigned long afsr, afar, error_bits;
	int reported;

	/* Latch error status. */
	afar = upa_readq(afar_reg);
	afsr = upa_readq(afsr_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(PSYCHO_CEAFSR_PPIO | PSYCHO_CEAFSR_PDRD | PSYCHO_CEAFSR_PDWR |
		 PSYCHO_CEAFSR_SPIO | PSYCHO_CEAFSR_SDRD | PSYCHO_CEAFSR_SDWR);
	if (!error_bits)
		return IRQ_NONE;
	upa_writeq(error_bits, afsr_reg);

	/* Log the error. */
	printk("%s: Correctable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & PSYCHO_CEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & PSYCHO_CEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & PSYCHO_CEAFSR_PDWR) ?
		   "DMA Write" : "???")))));

	/* XXX Use syndrome and afar to print out module string just like
	 * XXX UDB CE trap handler does... -DaveM
	 */
	printk("%s: syndrome[%02lx] bytemask[%04lx] dword_offset[%lx] "
	       "UPA_MID[%02lx] was_block(%d)\n",
	       pbm->name,
	       (afsr & PSYCHO_CEAFSR_ESYND) >> 48UL,
	       (afsr & PSYCHO_CEAFSR_BMSK) >> 32UL,
	       (afsr & PSYCHO_CEAFSR_DOFF) >> 29UL,
	       (afsr & PSYCHO_CEAFSR_MID) >> 24UL,
	       ((afsr & PSYCHO_CEAFSR_BLK) ? 1 : 0));
	printk("%s: CE AFAR [%016lx]\n", pbm->name, afar);
	printk("%s: CE Secondary errors [", pbm->name);
	reported = 0;
	if (afsr & PSYCHO_CEAFSR_SPIO) {
		reported++;
		printk("(PIO)");
	}
	if (afsr & PSYCHO_CEAFSR_SDRD) {
		reported++;
		printk("(DMA Read)");
	}
	if (afsr & PSYCHO_CEAFSR_SDWR) {
		reported++;
		printk("(DMA Write)");
	}
	if (!reported)
		printk("(none)");
	printk("]\n");

	return IRQ_HANDLED;
}