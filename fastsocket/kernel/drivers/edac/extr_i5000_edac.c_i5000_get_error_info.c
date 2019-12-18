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
struct mem_ctl_info {struct i5000_pvt* pvt_info; } ;
struct i5000_pvt {int /*<<< orphan*/  branchmap_werrors; } ;
struct i5000_error_info {int ferr_fat_fbd; int nerr_fat_fbd; int ferr_nf_fbd; int nerr_nf_fbd; int recmemb; int redmemb; scalar_t__ recmema; scalar_t__ nrecmemb; scalar_t__ nrecmema; } ;

/* Variables and functions */
 int /*<<< orphan*/  FERR_FAT_FBD ; 
 int FERR_FAT_FBDCHAN ; 
 int FERR_FAT_MASK ; 
 int /*<<< orphan*/  FERR_NF_FBD ; 
 int FERR_NF_MASK ; 
 int /*<<< orphan*/  NERR_FAT_FBD ; 
 int /*<<< orphan*/  NERR_NF_FBD ; 
 int /*<<< orphan*/  NRECMEMA ; 
 int /*<<< orphan*/  NRECMEMB ; 
 int /*<<< orphan*/  RECMEMA ; 
 int /*<<< orphan*/  RECMEMB ; 
 int /*<<< orphan*/  REDMEMB ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i5000_get_error_info(struct mem_ctl_info *mci,
				 struct i5000_error_info *info)
{
	struct i5000_pvt *pvt;
	u32 value;

	pvt = mci->pvt_info;

	/* read in the 1st FATAL error register */
	pci_read_config_dword(pvt->branchmap_werrors, FERR_FAT_FBD, &value);

	/* Mask only the bits that the doc says are valid
	 */
	value &= (FERR_FAT_FBDCHAN | FERR_FAT_MASK);

	/* If there is an error, then read in the */
	/* NEXT FATAL error register and the Memory Error Log Register A */
	if (value & FERR_FAT_MASK) {
		info->ferr_fat_fbd = value;

		/* harvest the various error data we need */
		pci_read_config_dword(pvt->branchmap_werrors,
				NERR_FAT_FBD, &info->nerr_fat_fbd);
		pci_read_config_word(pvt->branchmap_werrors,
				NRECMEMA, &info->nrecmema);
		pci_read_config_word(pvt->branchmap_werrors,
				NRECMEMB, &info->nrecmemb);

		/* Clear the error bits, by writing them back */
		pci_write_config_dword(pvt->branchmap_werrors,
				FERR_FAT_FBD, value);
	} else {
		info->ferr_fat_fbd = 0;
		info->nerr_fat_fbd = 0;
		info->nrecmema = 0;
		info->nrecmemb = 0;
	}

	/* read in the 1st NON-FATAL error register */
	pci_read_config_dword(pvt->branchmap_werrors, FERR_NF_FBD, &value);

	/* If there is an error, then read in the 1st NON-FATAL error
	 * register as well */
	if (value & FERR_NF_MASK) {
		info->ferr_nf_fbd = value;

		/* harvest the various error data we need */
		pci_read_config_dword(pvt->branchmap_werrors,
				NERR_NF_FBD, &info->nerr_nf_fbd);
		pci_read_config_word(pvt->branchmap_werrors,
				RECMEMA, &info->recmema);
		pci_read_config_dword(pvt->branchmap_werrors,
				RECMEMB, &info->recmemb);
		pci_read_config_dword(pvt->branchmap_werrors,
				REDMEMB, &info->redmemb);

		/* Clear the error bits, by writing them back */
		pci_write_config_dword(pvt->branchmap_werrors,
				FERR_NF_FBD, value);
	} else {
		info->ferr_nf_fbd = 0;
		info->nerr_nf_fbd = 0;
		info->recmema = 0;
		info->recmemb = 0;
		info->redmemb = 0;
	}
}