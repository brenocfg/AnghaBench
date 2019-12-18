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
struct of_device {TYPE_2__ dev; } ;
struct iommu {int write_complete_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSIO_ICLR_SLOT0 ; 
 int /*<<< orphan*/  SYSIO_ICLR_SLOT1 ; 
 int /*<<< orphan*/  SYSIO_ICLR_SLOT2 ; 
 int /*<<< orphan*/  SYSIO_ICLR_SLOT3 ; 
 unsigned int build_irq (int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  prom_halt () ; 
 int /*<<< orphan*/  prom_printf (char*,unsigned int) ; 
 unsigned long sysio_imap_to_iclr (unsigned long) ; 
 unsigned long* sysio_irq_offsets ; 

__attribute__((used)) static unsigned int sbus_build_irq(struct of_device *op, unsigned int ino)
{
	struct iommu *iommu = op->dev.archdata.iommu;
	unsigned long reg_base = iommu->write_complete_reg - 0x2000UL;
	unsigned long imap, iclr;
	int sbus_level = 0;

	imap = sysio_irq_offsets[ino];
	if (imap == ((unsigned long)-1)) {
		prom_printf("get_irq_translations: Bad SYSIO INO[%x]\n",
			    ino);
		prom_halt();
	}
	imap += reg_base;

	/* SYSIO inconsistency.  For external SLOTS, we have to select
	 * the right ICLR register based upon the lower SBUS irq level
	 * bits.
	 */
	if (ino >= 0x20) {
		iclr = sysio_imap_to_iclr(imap);
	} else {
		int sbus_slot = (ino & 0x18)>>3;
		
		sbus_level = ino & 0x7;

		switch(sbus_slot) {
		case 0:
			iclr = reg_base + SYSIO_ICLR_SLOT0;
			break;
		case 1:
			iclr = reg_base + SYSIO_ICLR_SLOT1;
			break;
		case 2:
			iclr = reg_base + SYSIO_ICLR_SLOT2;
			break;
		default:
		case 3:
			iclr = reg_base + SYSIO_ICLR_SLOT3;
			break;
		};

		iclr += ((unsigned long)sbus_level - 1UL) * 8UL;
	}
	return build_irq(sbus_level, iclr, imap);
}