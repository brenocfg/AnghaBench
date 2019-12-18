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
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {struct i7300_pvt* pvt_info; } ;
struct i7300_pvt {int /*<<< orphan*/  tmp_prt_buffer; int /*<<< orphan*/  pci_dev_16_1_fsb_addr_map; int /*<<< orphan*/  pci_dev_16_2_fsb_err_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FERR_FAT_FBD ; 
 unsigned long FERR_FAT_FBD_ERR_MASK ; 
 int /*<<< orphan*/  FERR_GLOBAL_LO ; 
 int /*<<< orphan*/  FERR_NF_FBD ; 
 unsigned long FERR_NF_FBD_ERR_MASK ; 
 char* GET_ERR_FROM_TABLE (int /*<<< orphan*/ ,unsigned long) ; 
 int GET_FBD_FAT_IDX (unsigned long) ; 
 scalar_t__ IS_SECOND_CH (unsigned long) ; 
 int /*<<< orphan*/  NRECMEMA ; 
 unsigned int NRECMEMA_BANK (int /*<<< orphan*/ ) ; 
 unsigned int NRECMEMA_RANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NRECMEMB ; 
 unsigned int NRECMEMB_CAS (unsigned long) ; 
 int NRECMEMB_IS_WR (unsigned long) ; 
 unsigned int NRECMEMB_RAS (unsigned long) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RECMEMA ; 
 unsigned int RECMEMA_BANK (int /*<<< orphan*/ ) ; 
 unsigned int RECMEMA_RANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECMEMB ; 
 unsigned int RECMEMB_CAS (unsigned long) ; 
 int RECMEMB_IS_WR (unsigned long) ; 
 unsigned int RECMEMB_RAS (unsigned long) ; 
 int /*<<< orphan*/  REDMEMA ; 
 int /*<<< orphan*/  REDMEMB ; 
 int /*<<< orphan*/  edac_mc_handle_fbd_ce (struct mem_ctl_info*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_fbd_ue (struct mem_ctl_info*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ferr_fat_fbd_name ; 
 int /*<<< orphan*/  ferr_nf_fbd_name ; 
 unsigned long find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static void i7300_process_fbd_error(struct mem_ctl_info *mci)
{
	struct i7300_pvt *pvt;
	u32 errnum, value;
	u16 val16;
	unsigned branch, channel, bank, rank, cas, ras;
	u32 syndrome;

	unsigned long errors;
	const char *specific;
	bool is_wr;

	pvt = mci->pvt_info;

	/* read in the 1st FATAL error register */
	pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_FAT_FBD, &value);
	if (unlikely(value & FERR_FAT_FBD_ERR_MASK)) {
		errors = value & FERR_FAT_FBD_ERR_MASK ;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_fat_fbd_name));
		specific = GET_ERR_FROM_TABLE(ferr_fat_fbd_name, errnum);

		branch = (GET_FBD_FAT_IDX(value) == 2) ? 1 : 0;
		pci_read_config_word(pvt->pci_dev_16_1_fsb_addr_map,
				     NRECMEMA, &val16);
		bank = NRECMEMA_BANK(val16);
		rank = NRECMEMA_RANK(val16);

		pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				NRECMEMB, &value);

		is_wr = NRECMEMB_IS_WR(value);
		cas = NRECMEMB_CAS(value);
		ras = NRECMEMB_RAS(value);

		snprintf(pvt->tmp_prt_buffer, PAGE_SIZE,
			"FATAL (Branch=%d DRAM-Bank=%d %s "
			"RAS=%d CAS=%d Err=0x%lx (%s))",
			branch, bank,
			is_wr ? "RDWR" : "RD",
			ras, cas,
			errors, specific);

		/* Call the helper to output message */
		edac_mc_handle_fbd_ue(mci, rank, branch << 1,
				      (branch << 1) + 1,
				      pvt->tmp_prt_buffer);
	}

	/* read in the 1st NON-FATAL error register */
	pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			      FERR_NF_FBD, &value);
	if (unlikely(value & FERR_NF_FBD_ERR_MASK)) {
		errors = value & FERR_NF_FBD_ERR_MASK;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_nf_fbd_name));
		specific = GET_ERR_FROM_TABLE(ferr_nf_fbd_name, errnum);

		/* Clear the error bit */
		pci_write_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
				       FERR_GLOBAL_LO, value);

		pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
			REDMEMA, &syndrome);

		branch = (GET_FBD_FAT_IDX(value) == 2) ? 1 : 0;
		pci_read_config_word(pvt->pci_dev_16_1_fsb_addr_map,
				     RECMEMA, &val16);
		bank = RECMEMA_BANK(val16);
		rank = RECMEMA_RANK(val16);

		pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				RECMEMB, &value);

		is_wr = RECMEMB_IS_WR(value);
		cas = RECMEMB_CAS(value);
		ras = RECMEMB_RAS(value);

		pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map,
				     REDMEMB, &value);

		channel = (branch << 1);
		if (IS_SECOND_CH(value))
			channel++;

		/* Form out message */
		snprintf(pvt->tmp_prt_buffer, PAGE_SIZE,
			"Corrected error (Branch=%d, Channel %d), "
			" DRAM-Bank=%d %s "
			"RAS=%d CAS=%d, CE Err=0x%lx, Syndrome=0x%08x(%s))",
			branch, channel,
			bank,
			is_wr ? "RDWR" : "RD",
			ras, cas,
			errors, syndrome, specific);

		/*
		 * Call the helper to output message
		 * NOTE: Errors are reported per-branch, and not per-channel
		 *	 Currently, we don't know how to identify the right
		 *	 channel.
		 */
		edac_mc_handle_fbd_ce(mci, rank, channel,
				      pvt->tmp_prt_buffer);
	}
	return;
}