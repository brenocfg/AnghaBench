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
typedef  int /*<<< orphan*/  vme_cycle_t ;
typedef  int /*<<< orphan*/  vme_address_t ;
struct vme_slave_resource {unsigned int number; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__* TSI148_LCSR_IT ; 
 unsigned int TSI148_LCSR_ITAT_2eSST ; 
 unsigned int TSI148_LCSR_ITAT_2eSSTB ; 
 unsigned int TSI148_LCSR_ITAT_2eSSTM_160 ; 
 unsigned int TSI148_LCSR_ITAT_2eSSTM_267 ; 
 unsigned int TSI148_LCSR_ITAT_2eSSTM_320 ; 
 unsigned int TSI148_LCSR_ITAT_2eSSTM_M ; 
 unsigned int TSI148_LCSR_ITAT_2eVME ; 
 unsigned int TSI148_LCSR_ITAT_AS_A16 ; 
 unsigned int TSI148_LCSR_ITAT_AS_A24 ; 
 unsigned int TSI148_LCSR_ITAT_AS_A32 ; 
 unsigned int TSI148_LCSR_ITAT_AS_A64 ; 
 unsigned int TSI148_LCSR_ITAT_AS_M ; 
 unsigned int TSI148_LCSR_ITAT_BLT ; 
 unsigned int TSI148_LCSR_ITAT_DATA ; 
 unsigned int TSI148_LCSR_ITAT_EN ; 
 unsigned int TSI148_LCSR_ITAT_MBLT ; 
 unsigned int TSI148_LCSR_ITAT_NPRIV ; 
 unsigned int TSI148_LCSR_ITAT_PGM ; 
 unsigned int TSI148_LCSR_ITAT_SUPR ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITAT ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITEAL ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITEAU ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITOFL ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITOFU ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITSAL ; 
 scalar_t__ TSI148_LCSR_OFFSET_ITSAU ; 
 int /*<<< orphan*/  VME_2eSST ; 
 int /*<<< orphan*/  VME_2eSST160 ; 
 int /*<<< orphan*/  VME_2eSST267 ; 
 int /*<<< orphan*/  VME_2eSST320 ; 
 int /*<<< orphan*/  VME_2eSSTB ; 
 int /*<<< orphan*/  VME_2eVME ; 
 int /*<<< orphan*/  VME_A16 ; 
 int /*<<< orphan*/  VME_A24 ; 
 int /*<<< orphan*/  VME_A32 ; 
 int /*<<< orphan*/  VME_A64 ; 
 int /*<<< orphan*/  VME_BLT ; 
 int /*<<< orphan*/  VME_DATA ; 
 int /*<<< orphan*/  VME_MBLT ; 
 int /*<<< orphan*/  VME_PROG ; 
 int /*<<< orphan*/  VME_SUPER ; 
 int /*<<< orphan*/  VME_USER ; 
 unsigned int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  reg_join (unsigned int,unsigned int,unsigned long long*) ; 
 TYPE_1__* tsi148_bridge ; 

int tsi148_slave_get(struct vme_slave_resource *image, int *enabled,
	unsigned long long *vme_base, unsigned long long *size,
	dma_addr_t *pci_base, vme_address_t *aspace, vme_cycle_t *cycle)
{
	unsigned int i, granularity = 0, ctl = 0;
	unsigned int vme_base_low, vme_base_high;
	unsigned int vme_bound_low, vme_bound_high;
	unsigned int pci_offset_low, pci_offset_high;
	unsigned long long vme_bound, pci_offset;


	i = image->number;

	/* Read registers */
	ctl = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITAT);

	vme_base_high = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITSAU);
	vme_base_low = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITSAL);
	vme_bound_high = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITEAU);
	vme_bound_low = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITEAL);
	pci_offset_high = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITOFU);
	pci_offset_low = ioread32be(tsi148_bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITOFL);

	/* Convert 64-bit variables to 2x 32-bit variables */
	reg_join(vme_base_high, vme_base_low, vme_base);
	reg_join(vme_bound_high, vme_bound_low, &vme_bound);
	reg_join(pci_offset_high, pci_offset_low, &pci_offset);

	*pci_base = (dma_addr_t)vme_base + pci_offset;

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;

	if (ctl & TSI148_LCSR_ITAT_EN)
		*enabled = 1;

	if ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A16) {
		granularity = 0x10;
		*aspace |= VME_A16;
	}
	if ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A24) {
		granularity = 0x1000;
		*aspace |= VME_A24;
	}
	if ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A32) {
		granularity = 0x10000;
		*aspace |= VME_A32;
	}
	if ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A64) {
		granularity = 0x10000;
		*aspace |= VME_A64;
	}

	/* Need granularity before we set the size */
	*size = (unsigned long long)((vme_bound - *vme_base) + granularity);


	if ((ctl & TSI148_LCSR_ITAT_2eSSTM_M) == TSI148_LCSR_ITAT_2eSSTM_160)
		*cycle |= VME_2eSST160;
	if ((ctl & TSI148_LCSR_ITAT_2eSSTM_M) == TSI148_LCSR_ITAT_2eSSTM_267)
		*cycle |= VME_2eSST267;
	if ((ctl & TSI148_LCSR_ITAT_2eSSTM_M) == TSI148_LCSR_ITAT_2eSSTM_320)
		*cycle |= VME_2eSST320;

	if (ctl & TSI148_LCSR_ITAT_BLT)
		*cycle |= VME_BLT;
	if (ctl & TSI148_LCSR_ITAT_MBLT)
		*cycle |= VME_MBLT;
	if (ctl & TSI148_LCSR_ITAT_2eVME)
		*cycle |= VME_2eVME;
	if (ctl & TSI148_LCSR_ITAT_2eSST)
		*cycle |= VME_2eSST;
	if (ctl & TSI148_LCSR_ITAT_2eSSTB)
		*cycle |= VME_2eSSTB;

	if (ctl & TSI148_LCSR_ITAT_SUPR)
		*cycle |= VME_SUPER;
	if (ctl & TSI148_LCSR_ITAT_NPRIV)
		*cycle |= VME_USER;
	if (ctl & TSI148_LCSR_ITAT_PGM)
		*cycle |= VME_PROG;
	if (ctl & TSI148_LCSR_ITAT_DATA)
		*cycle |= VME_DATA;

	return 0;
}