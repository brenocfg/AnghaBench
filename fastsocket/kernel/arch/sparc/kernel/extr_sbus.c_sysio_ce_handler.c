#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct iommu* iommu; } ;
struct TYPE_4__ {TYPE_1__ archdata; } ;
struct of_device {int /*<<< orphan*/  node; TYPE_2__ dev; } ;
struct iommu {int write_complete_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long SYSIO_CEAFSR_DOFF ; 
 unsigned long SYSIO_CEAFSR_ESYND ; 
 unsigned long SYSIO_CEAFSR_MID ; 
 unsigned long SYSIO_CEAFSR_PDRD ; 
 unsigned long SYSIO_CEAFSR_PDWR ; 
 unsigned long SYSIO_CEAFSR_PPIO ; 
 unsigned long SYSIO_CEAFSR_SDRD ; 
 unsigned long SYSIO_CEAFSR_SDWR ; 
 unsigned long SYSIO_CEAFSR_SIZE ; 
 unsigned long SYSIO_CEAFSR_SPIO ; 
 unsigned long SYSIO_CE_AFAR ; 
 unsigned long SYSIO_CE_AFSR ; 
 int of_getintprop_default (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t sysio_ce_handler(int irq, void *dev_id)
{
	struct of_device *op = dev_id;
	struct iommu *iommu = op->dev.archdata.iommu;
	unsigned long reg_base = iommu->write_complete_reg - 0x2000UL;
	unsigned long afsr_reg, afar_reg;
	unsigned long afsr, afar, error_bits;
	int reported, portid;

	afsr_reg = reg_base + SYSIO_CE_AFSR;
	afar_reg = reg_base + SYSIO_CE_AFAR;

	/* Latch error status. */
	afsr = upa_readq(afsr_reg);
	afar = upa_readq(afar_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SYSIO_CEAFSR_PPIO | SYSIO_CEAFSR_PDRD | SYSIO_CEAFSR_PDWR |
		 SYSIO_CEAFSR_SPIO | SYSIO_CEAFSR_SDRD | SYSIO_CEAFSR_SDWR);
	upa_writeq(error_bits, afsr_reg);

	portid = of_getintprop_default(op->node, "portid", -1);

	printk("SYSIO[%x]: Correctable ECC Error, primary error type[%s]\n",
	       portid,
	       (((error_bits & SYSIO_CEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SYSIO_CEAFSR_PDRD) ?
		  "DVMA Read" :
		  ((error_bits & SYSIO_CEAFSR_PDWR) ?
		   "DVMA Write" : "???")))));

	/* XXX Use syndrome and afar to print out module string just like
	 * XXX UDB CE trap handler does... -DaveM
	 */
	printk("SYSIO[%x]: DOFF[%lx] ECC Syndrome[%lx] Size[%lx] MID[%lx]\n",
	       portid,
	       (afsr & SYSIO_CEAFSR_DOFF) >> 45UL,
	       (afsr & SYSIO_CEAFSR_ESYND) >> 48UL,
	       (afsr & SYSIO_CEAFSR_SIZE) >> 42UL,
	       (afsr & SYSIO_CEAFSR_MID) >> 37UL);
	printk("SYSIO[%x]: AFAR[%016lx]\n", portid, afar);

	printk("SYSIO[%x]: Secondary CE errors [", portid);
	reported = 0;
	if (afsr & SYSIO_CEAFSR_SPIO) {
		reported++;
		printk("(PIO)");
	}
	if (afsr & SYSIO_CEAFSR_SDRD) {
		reported++;
		printk("(DVMA Read)");
	}
	if (afsr & SYSIO_CEAFSR_SDWR) {
		reported++;
		printk("(DVMA Write)");
	}
	if (!reported)
		printk("(none)");
	printk("]\n");

	return IRQ_HANDLED;
}