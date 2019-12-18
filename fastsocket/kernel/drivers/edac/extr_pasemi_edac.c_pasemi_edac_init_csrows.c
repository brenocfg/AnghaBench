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
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int nr_csrows; struct csrow_info* csrows; } ;
struct csrow_info {int nr_pages; int first_page; int last_page; int edac_mode; int /*<<< orphan*/  dtype; int /*<<< orphan*/  mtype; int /*<<< orphan*/  grain; scalar_t__ page_mask; } ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_UNKNOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ MCDRAM_RANKCFG ; 
 int MCDRAM_RANKCFG_EN ; 
 int MCDRAM_RANKCFG_TYPE_SIZE_M ; 
 int MCDRAM_RANKCFG_TYPE_SIZE_S ; 
 int /*<<< orphan*/  MEM_DDR ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PASEMI_EDAC_ERROR_GRAIN ; 
 int /*<<< orphan*/  edac_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,int) ; 
 int last_page_in_mmc ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static int pasemi_edac_init_csrows(struct mem_ctl_info *mci,
				   struct pci_dev *pdev,
				   enum edac_type edac_mode)
{
	struct csrow_info *csrow;
	u32 rankcfg;
	int index;

	for (index = 0; index < mci->nr_csrows; index++) {
		csrow = &mci->csrows[index];

		pci_read_config_dword(pdev,
				      MCDRAM_RANKCFG + (index * 12),
				      &rankcfg);

		if (!(rankcfg & MCDRAM_RANKCFG_EN))
			continue;

		switch ((rankcfg & MCDRAM_RANKCFG_TYPE_SIZE_M) >>
			MCDRAM_RANKCFG_TYPE_SIZE_S) {
		case 0:
			csrow->nr_pages = 128 << (20 - PAGE_SHIFT);
			break;
		case 1:
			csrow->nr_pages = 256 << (20 - PAGE_SHIFT);
			break;
		case 2:
		case 3:
			csrow->nr_pages = 512 << (20 - PAGE_SHIFT);
			break;
		case 4:
			csrow->nr_pages = 1024 << (20 - PAGE_SHIFT);
			break;
		case 5:
			csrow->nr_pages = 2048 << (20 - PAGE_SHIFT);
			break;
		default:
			edac_mc_printk(mci, KERN_ERR,
				"Unrecognized Rank Config. rankcfg=%u\n",
				rankcfg);
			return -EINVAL;
		}

		csrow->first_page = last_page_in_mmc;
		csrow->last_page = csrow->first_page + csrow->nr_pages - 1;
		last_page_in_mmc += csrow->nr_pages;
		csrow->page_mask = 0;
		csrow->grain = PASEMI_EDAC_ERROR_GRAIN;
		csrow->mtype = MEM_DDR;
		csrow->dtype = DEV_UNKNOWN;
		csrow->edac_mode = edac_mode;
	}
	return 0;
}