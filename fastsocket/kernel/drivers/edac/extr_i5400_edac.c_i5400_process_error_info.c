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
struct mem_ctl_info {int dummy; } ;
struct i5400_error_info {int ferr_fat_fbd; } ;

/* Variables and functions */
 int FERR_FAT_MASK ; 
 int /*<<< orphan*/  i5400_proccess_non_recoverable_info (struct mem_ctl_info*,struct i5400_error_info*,int) ; 
 int /*<<< orphan*/  i5400_process_nonfatal_error_info (struct mem_ctl_info*,struct i5400_error_info*) ; 

__attribute__((used)) static void i5400_process_error_info(struct mem_ctl_info *mci,
				struct i5400_error_info *info)
{	u32 allErrors;

	/* First handle any fatal errors that occurred */
	allErrors = (info->ferr_fat_fbd & FERR_FAT_MASK);
	i5400_proccess_non_recoverable_info(mci, info, allErrors);

	/* now handle any non-fatal errors that occurred */
	i5400_process_nonfatal_error_info(mci, info);
}