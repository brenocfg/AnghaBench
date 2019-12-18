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
 unsigned long SYSIO_UEAFSR_DOFF ; 
 unsigned long SYSIO_UEAFSR_MID ; 
 unsigned long SYSIO_UEAFSR_PDRD ; 
 unsigned long SYSIO_UEAFSR_PDWR ; 
 unsigned long SYSIO_UEAFSR_PPIO ; 
 unsigned long SYSIO_UEAFSR_SDRD ; 
 unsigned long SYSIO_UEAFSR_SDWR ; 
 unsigned long SYSIO_UEAFSR_SIZE ; 
 unsigned long SYSIO_UEAFSR_SPIO ; 
 unsigned long SYSIO_UE_AFAR ; 
 unsigned long SYSIO_UE_AFSR ; 
 int of_getintprop_default (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t sysio_ue_handler(int irq, void *dev_id)
{
	struct of_device *op = dev_id;
	struct iommu *iommu = op->dev.archdata.iommu;
	unsigned long reg_base = iommu->write_complete_reg - 0x2000UL;
	unsigned long afsr_reg, afar_reg;
	unsigned long afsr, afar, error_bits;
	int reported, portid;

	afsr_reg = reg_base + SYSIO_UE_AFSR;
	afar_reg = reg_base + SYSIO_UE_AFAR;

	/* Latch error status. */
	afsr = upa_readq(afsr_reg);
	afar = upa_readq(afar_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SYSIO_UEAFSR_PPIO | SYSIO_UEAFSR_PDRD | SYSIO_UEAFSR_PDWR |
		 SYSIO_UEAFSR_SPIO | SYSIO_UEAFSR_SDRD | SYSIO_UEAFSR_SDWR);
	upa_writeq(error_bits, afsr_reg);

	portid = of_getintprop_default(op->node, "portid", -1);

	/* Log the error. */
	printk("SYSIO[%x]: Uncorrectable ECC Error, primary error type[%s]\n",
	       portid,
	       (((error_bits & SYSIO_UEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SYSIO_UEAFSR_PDRD) ?
		  "DVMA Read" :
		  ((error_bits & SYSIO_UEAFSR_PDWR) ?
		   "DVMA Write" : "???")))));
	printk("SYSIO[%x]: DOFF[%lx] SIZE[%lx] MID[%lx]\n",
	       portid,
	       (afsr & SYSIO_UEAFSR_DOFF) >> 45UL,
	       (afsr & SYSIO_UEAFSR_SIZE) >> 42UL,
	       (afsr & SYSIO_UEAFSR_MID) >> 37UL);
	printk("SYSIO[%x]: AFAR[%016lx]\n", portid, afar);
	printk("SYSIO[%x]: Secondary UE errors [", portid);
	reported = 0;
	if (afsr & SYSIO_UEAFSR_SPIO) {
		reported++;
		printk("(PIO)");
	}
	if (afsr & SYSIO_UEAFSR_SDRD) {
		reported++;
		printk("(DVMA Read)");
	}
	if (afsr & SYSIO_UEAFSR_SDWR) {
		reported++;
		printk("(DVMA Write)");
	}
	if (!reported)
		printk("(none)");
	printk("]\n");

	return IRQ_HANDLED;
}