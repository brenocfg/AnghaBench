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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ strbuf_enabled; } ;
struct pci_pbm_info {unsigned long pbm_regs; TYPE_1__ stc; int /*<<< orphan*/  name; struct iommu* iommu; } ;
struct iommu {int /*<<< orphan*/  lock; scalar_t__ iommu_control; } ;
typedef  enum schizo_error_type { ____Placeholder_schizo_error_type } schizo_error_type ;

/* Variables and functions */
 unsigned long IOMMU_PAGE_SHIFT ; 
 int SCHIZO_IOMMU_CTRL_DENAB ; 
 int SCHIZO_IOMMU_CTRL_XLTEERR ; 
 int SCHIZO_IOMMU_CTRL_XLTESTAT ; 
 scalar_t__ SCHIZO_IOMMU_DATA ; 
 unsigned long SCHIZO_IOMMU_DATA_CACHE ; 
 unsigned long SCHIZO_IOMMU_DATA_PPAGE ; 
 unsigned long SCHIZO_IOMMU_DATA_VALID ; 
 scalar_t__ SCHIZO_IOMMU_TAG ; 
 unsigned long SCHIZO_IOMMU_TAG_CTXT ; 
 unsigned long SCHIZO_IOMMU_TAG_ERR ; 
 unsigned long SCHIZO_IOMMU_TAG_ERRSTS ; 
 unsigned long SCHIZO_IOMMU_TAG_SIZE ; 
 unsigned long SCHIZO_IOMMU_TAG_STREAM ; 
 unsigned long SCHIZO_IOMMU_TAG_VPAGE ; 
 unsigned long SCHIZO_IOMMU_TAG_WRITE ; 
 int /*<<< orphan*/  __schizo_check_stc_error_pbm (struct pci_pbm_info*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

__attribute__((used)) static void schizo_check_iommu_error_pbm(struct pci_pbm_info *pbm,
					 enum schizo_error_type type)
{
	struct iommu *iommu = pbm->iommu;
	unsigned long iommu_tag[16];
	unsigned long iommu_data[16];
	unsigned long flags;
	u64 control;
	int i;

	spin_lock_irqsave(&iommu->lock, flags);
	control = upa_readq(iommu->iommu_control);
	if (control & SCHIZO_IOMMU_CTRL_XLTEERR) {
		unsigned long base;
		char *type_string;

		/* Clear the error encountered bit. */
		control &= ~SCHIZO_IOMMU_CTRL_XLTEERR;
		upa_writeq(control, iommu->iommu_control);

		switch((control & SCHIZO_IOMMU_CTRL_XLTESTAT) >> 25UL) {
		case 0:
			type_string = "Protection Error";
			break;
		case 1:
			type_string = "Invalid Error";
			break;
		case 2:
			type_string = "TimeOut Error";
			break;
		case 3:
		default:
			type_string = "ECC Error";
			break;
		};
		printk("%s: IOMMU Error, type[%s]\n",
		       pbm->name, type_string);

		/* Put the IOMMU into diagnostic mode and probe
		 * it's TLB for entries with error status.
		 *
		 * It is very possible for another DVMA to occur
		 * while we do this probe, and corrupt the system
		 * further.  But we are so screwed at this point
		 * that we are likely to crash hard anyways, so
		 * get as much diagnostic information to the
		 * console as we can.
		 */
		upa_writeq(control | SCHIZO_IOMMU_CTRL_DENAB,
			   iommu->iommu_control);

		base = pbm->pbm_regs;

		for (i = 0; i < 16; i++) {
			iommu_tag[i] =
				upa_readq(base + SCHIZO_IOMMU_TAG + (i * 8UL));
			iommu_data[i] =
				upa_readq(base + SCHIZO_IOMMU_DATA + (i * 8UL));

			/* Now clear out the entry. */
			upa_writeq(0, base + SCHIZO_IOMMU_TAG + (i * 8UL));
			upa_writeq(0, base + SCHIZO_IOMMU_DATA + (i * 8UL));
		}

		/* Leave diagnostic mode. */
		upa_writeq(control, iommu->iommu_control);

		for (i = 0; i < 16; i++) {
			unsigned long tag, data;

			tag = iommu_tag[i];
			if (!(tag & SCHIZO_IOMMU_TAG_ERR))
				continue;

			data = iommu_data[i];
			switch((tag & SCHIZO_IOMMU_TAG_ERRSTS) >> 23UL) {
			case 0:
				type_string = "Protection Error";
				break;
			case 1:
				type_string = "Invalid Error";
				break;
			case 2:
				type_string = "TimeOut Error";
				break;
			case 3:
			default:
				type_string = "ECC Error";
				break;
			};
			printk("%s: IOMMU TAG(%d)[error(%s) ctx(%x) wr(%d) str(%d) "
			       "sz(%dK) vpg(%08lx)]\n",
			       pbm->name, i, type_string,
			       (int)((tag & SCHIZO_IOMMU_TAG_CTXT) >> 25UL),
			       ((tag & SCHIZO_IOMMU_TAG_WRITE) ? 1 : 0),
			       ((tag & SCHIZO_IOMMU_TAG_STREAM) ? 1 : 0),
			       ((tag & SCHIZO_IOMMU_TAG_SIZE) ? 64 : 8),
			       (tag & SCHIZO_IOMMU_TAG_VPAGE) << IOMMU_PAGE_SHIFT);
			printk("%s: IOMMU DATA(%d)[valid(%d) cache(%d) ppg(%016lx)]\n",
			       pbm->name, i,
			       ((data & SCHIZO_IOMMU_DATA_VALID) ? 1 : 0),
			       ((data & SCHIZO_IOMMU_DATA_CACHE) ? 1 : 0),
			       (data & SCHIZO_IOMMU_DATA_PPAGE) << IOMMU_PAGE_SHIFT);
		}
	}
	if (pbm->stc.strbuf_enabled)
		__schizo_check_stc_error_pbm(pbm, type);
	spin_unlock_irqrestore(&iommu->lock, flags);
}