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
typedef  scalar_t__ vme_width_t ;
typedef  int /*<<< orphan*/  vme_cycle_t ;
typedef  scalar_t__ vme_address_t ;
struct vme_master_resource {unsigned int number; } ;
struct TYPE_4__ {scalar_t__ base; } ;
struct TYPE_3__ {int wrPostEnable; } ;

/* Variables and functions */
 scalar_t__* CA91CX42_LSI_BD ; 
 scalar_t__* CA91CX42_LSI_BS ; 
 scalar_t__* CA91CX42_LSI_CTL ; 
 unsigned int CA91CX42_LSI_CTL_EN ; 
 unsigned int CA91CX42_LSI_CTL_PGM_PGM ; 
 unsigned int CA91CX42_LSI_CTL_SUPER_SUPR ; 
#define  CA91CX42_LSI_CTL_VAS_A16 137 
#define  CA91CX42_LSI_CTL_VAS_A24 136 
#define  CA91CX42_LSI_CTL_VAS_A32 135 
#define  CA91CX42_LSI_CTL_VAS_CRCSR 134 
 unsigned int CA91CX42_LSI_CTL_VAS_M ; 
#define  CA91CX42_LSI_CTL_VAS_USER1 133 
#define  CA91CX42_LSI_CTL_VAS_USER2 132 
 unsigned int CA91CX42_LSI_CTL_VCT_BLT ; 
#define  CA91CX42_LSI_CTL_VDW_D16 131 
#define  CA91CX42_LSI_CTL_VDW_D32 130 
#define  CA91CX42_LSI_CTL_VDW_D64 129 
#define  CA91CX42_LSI_CTL_VDW_D8 128 
 unsigned int CA91CX42_LSI_CTL_VDW_M ; 
 scalar_t__* CA91CX42_LSI_TO ; 
 scalar_t__ VME_A16 ; 
 scalar_t__ VME_A24 ; 
 scalar_t__ VME_A32 ; 
 int /*<<< orphan*/  VME_BLT ; 
 scalar_t__ VME_CRCSR ; 
 scalar_t__ VME_D16 ; 
 scalar_t__ VME_D32 ; 
 scalar_t__ VME_D64 ; 
 scalar_t__ VME_D8 ; 
 int /*<<< orphan*/  VME_DATA ; 
 int /*<<< orphan*/  VME_PROG ; 
 int /*<<< orphan*/  VME_SCT ; 
 int /*<<< orphan*/  VME_SUPER ; 
 int /*<<< orphan*/  VME_USER ; 
 scalar_t__ VME_USER1 ; 
 scalar_t__ VME_USER2 ; 
 TYPE_2__* ca91cx42_bridge ; 
 void* ioread32 (scalar_t__) ; 
 TYPE_1__* vmeOut ; 

int __ca91cx42_master_get(struct vme_master_resource *image, int *enabled,
	unsigned long long *vme_base, unsigned long long *size,
	vme_address_t *aspace, vme_cycle_t *cycle, vme_width_t *dwidth)
{
	unsigned int i, ctl;
	unsigned long long pci_base, pci_bound, vme_offset;

	i = image->number;

	ctl = ioread32(ca91cx42_bridge->base + CA91CX42_LSI_CTL[i]);

	pci_base = ioread32(ca91cx42_bridge->base + CA91CX42_LSI_BS[i]);
	vme_offset = ioread32(ca91cx42_bridge->base + CA91CX42_LSI_TO[i]);
	pci_bound = ioread32(ca91cx42_bridge->base + CA91CX42_LSI_BD[i]);

	*vme_base = pci_base + vme_offset;
	*size = (pci_bound - pci_base) + 0x1000;

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;
	*dwidth = 0;

	if (ctl & CA91CX42_LSI_CTL_EN)
		*enabled = 1;

	/* Setup address space */
	switch (ctl & CA91CX42_LSI_CTL_VAS_M) {
	case CA91CX42_LSI_CTL_VAS_A16:
		*aspace = VME_A16;
		break;
	case CA91CX42_LSI_CTL_VAS_A24:
		*aspace = VME_A24;
		break;
	case CA91CX42_LSI_CTL_VAS_A32:
		*aspace = VME_A32;
		break;
	case CA91CX42_LSI_CTL_VAS_CRCSR:
		*aspace = VME_CRCSR;
		break;
	case CA91CX42_LSI_CTL_VAS_USER1:
		*aspace = VME_USER1;
		break;
	case CA91CX42_LSI_CTL_VAS_USER2:
		*aspace = VME_USER2;
		break;
	}

	/* XXX Not sure howto check for MBLT */
	/* Setup cycle types */
	if (ctl & CA91CX42_LSI_CTL_VCT_BLT)
		*cycle |= VME_BLT;
	else
		*cycle |= VME_SCT;

	if (ctl & CA91CX42_LSI_CTL_SUPER_SUPR)
		*cycle |= VME_SUPER;
	else
		*cycle |= VME_USER;

	if (ctl & CA91CX42_LSI_CTL_PGM_PGM)
		*cycle = VME_PROG;
	else
		*cycle = VME_DATA;

	/* Setup data width */
	switch (ctl & CA91CX42_LSI_CTL_VDW_M) {
	case CA91CX42_LSI_CTL_VDW_D8:
		*dwidth = VME_D8;
		break;
	case CA91CX42_LSI_CTL_VDW_D16:
		*dwidth = VME_D16;
		break;
	case CA91CX42_LSI_CTL_VDW_D32:
		*dwidth = VME_D32;
		break;
	case CA91CX42_LSI_CTL_VDW_D64:
		*dwidth = VME_D64;
		break;
	}

/* XXX Prefetch stuff currently unsupported */
#if 0
	if (ctl & 0x40000000)
		vmeOut->wrPostEnable = 1;
#endif

	return 0;
}