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
struct mem_ctl_info {int dummy; } ;
struct i5400_error_info {int ferr_nf_fbd; int /*<<< orphan*/  redmemb; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDAC_MC_LABEL_LEN ; 
 unsigned long ERROR_NF_CORRECTABLE ; 
 unsigned long ERROR_NF_RECOVERABLE ; 
 unsigned long ERROR_NF_UNCORRECTABLE ; 
 int FERR_NF_MASK ; 
 int /*<<< orphan*/  KERN_EMERG ; 
 scalar_t__ REC_ECC_LOCATOR_ODD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf0 (char*,int,...) ; 
 int /*<<< orphan*/  edac_mc_handle_fbd_ce (struct mem_ctl_info*,int,int,char*) ; 
 int /*<<< orphan*/ * error_name ; 
 int extract_fbdchan_indx (int) ; 
 int find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 unsigned long from_nf_ferr (int) ; 
 int /*<<< orphan*/  i5400_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i5400_proccess_non_recoverable_info (struct mem_ctl_info*,struct i5400_error_info*,unsigned long) ; 
 char* rdwr_str (int) ; 
 int rec_bank (struct i5400_error_info*) ; 
 int rec_cas (struct i5400_error_info*) ; 
 int rec_rank (struct i5400_error_info*) ; 
 int rec_ras (struct i5400_error_info*) ; 
 int rec_rdwr (struct i5400_error_info*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char*,int,int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i5400_process_nonfatal_error_info(struct mem_ctl_info *mci,
					struct i5400_error_info *info)
{
	char msg[EDAC_MC_LABEL_LEN + 1 + 90 + 80];
	unsigned long allErrors;
	int branch;
	int channel;
	int bank;
	int rank;
	int rdwr;
	int ras, cas;
	int errnum;

	/* mask off the Error bits that are possible */
	allErrors = from_nf_ferr(info->ferr_nf_fbd & FERR_NF_MASK);
	if (!allErrors)
		return;		/* if no error, return now */

	/* ONLY ONE of the possible error bits will be set, as per the docs */

	if (allErrors & (ERROR_NF_UNCORRECTABLE | ERROR_NF_RECOVERABLE)) {
		i5400_proccess_non_recoverable_info(mci, info, allErrors);
		return;
	}

	/* Correctable errors */
	if (allErrors & ERROR_NF_CORRECTABLE) {
		debugf0("\tCorrected bits= 0x%lx\n", allErrors);

		branch = extract_fbdchan_indx(info->ferr_nf_fbd);

		channel = 0;
		if (REC_ECC_LOCATOR_ODD(info->redmemb))
			channel = 1;

		/* Convert channel to be based from zero, instead of
		 * from branch base of 0 */
		channel += branch;

		bank = rec_bank(info);
		rank = rec_rank(info);
		rdwr = rec_rdwr(info);
		ras = rec_ras(info);
		cas = rec_cas(info);

		/* Only 1 bit will be on */
		errnum = find_first_bit(&allErrors, ARRAY_SIZE(error_name));

		debugf0("\t\tCSROW= %d Channel= %d  (Branch %d "
			"DRAM Bank= %d rdwr= %s ras= %d cas= %d)\n",
			rank, channel, branch >> 1, bank,
			rdwr_str(rdwr), ras, cas);

		/* Form out message */
		snprintf(msg, sizeof(msg),
			 "Corrected error (Branch=%d DRAM-Bank=%d RDWR=%s "
			 "RAS=%d CAS=%d, CE Err=0x%lx (%s))",
			 branch >> 1, bank, rdwr_str(rdwr), ras, cas,
			 allErrors, error_name[errnum]);

		/* Call the helper to output message */
		edac_mc_handle_fbd_ce(mci, rank, channel, msg);

		return;
	}

	/* Miscelaneous errors */
	errnum = find_first_bit(&allErrors, ARRAY_SIZE(error_name));

	branch = extract_fbdchan_indx(info->ferr_nf_fbd);

	i5400_mc_printk(mci, KERN_EMERG,
			"Non-Fatal misc error (Branch=%d Err=%#lx (%s))",
			branch >> 1, allErrors, error_name[errnum]);
}