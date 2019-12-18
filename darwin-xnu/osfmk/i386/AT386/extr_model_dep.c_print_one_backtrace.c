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
typedef  int vm_offset_t ;
typedef  int uint32_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ boolean_t ;
typedef  int addr64_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int FP_ALIGNMENT_MASK ; 
 int FP_LR_OFFSET ; 
 int FP_LR_OFFSET64 ; 
 int FP_MAX_NUM_TO_EVALUATE ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ TRUE ; 
 int VM_MAX_KERNEL_ADDRESS ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 int ml_phys_read_double_64 (int) ; 
 int ml_phys_read_word (int) ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,char const*,int) ; 
 scalar_t__ pmap_find_phys (int /*<<< orphan*/ ,int) ; 

void
print_one_backtrace(pmap_t pmap, vm_offset_t topfp, const char *cur_marker,
	boolean_t is_64_bit)
{
	int		    i = 0;
	addr64_t	lr;
	addr64_t	fp;
	addr64_t	fp_for_ppn;
	ppnum_t		ppn;
	boolean_t	dump_kernel_stack;

	fp = topfp;
	fp_for_ppn = 0;
	ppn = (ppnum_t)NULL;

	if (fp >= VM_MIN_KERNEL_ADDRESS)
		dump_kernel_stack = TRUE;
	else
		dump_kernel_stack = FALSE;

	do {
		if ((fp == 0) || ((fp & FP_ALIGNMENT_MASK) != 0))
			break;
		if (dump_kernel_stack && ((fp < VM_MIN_KERNEL_ADDRESS) || (fp > VM_MAX_KERNEL_ADDRESS)))
			break;
		if ((!dump_kernel_stack) && (fp >=VM_MIN_KERNEL_ADDRESS))
			break;
			
        /* Check to see if current address will result in a different
           ppn than previously computed (to avoid recomputation) via
           (addr) ^ fp_for_ppn) >> PAGE_SHIFT) */

		if ((((fp + FP_LR_OFFSET) ^ fp_for_ppn) >> PAGE_SHIFT) != 0x0U) {
			ppn = pmap_find_phys(pmap, fp + FP_LR_OFFSET);
			fp_for_ppn = fp + (is_64_bit ? FP_LR_OFFSET64 : FP_LR_OFFSET);
		}
		if (ppn != (ppnum_t)NULL) {
			if (is_64_bit) {
				lr = ml_phys_read_double_64(((((vm_offset_t)ppn) << PAGE_SHIFT)) | ((fp + FP_LR_OFFSET64) & PAGE_MASK));
			} else {
				lr = ml_phys_read_word(((((vm_offset_t)ppn) << PAGE_SHIFT)) | ((fp + FP_LR_OFFSET) & PAGE_MASK));
			}
		} else {
			if (is_64_bit) {
				paniclog_append_noflush("%s\t  Could not read LR from frame at 0x%016llx\n", cur_marker, fp + FP_LR_OFFSET64);
			} else {
				paniclog_append_noflush("%s\t  Could not read LR from frame at 0x%08x\n", cur_marker, (uint32_t)(fp + FP_LR_OFFSET));
			}
			break;
		}
		if (((fp ^ fp_for_ppn) >> PAGE_SHIFT) != 0x0U) {
			ppn = pmap_find_phys(pmap, fp);
			fp_for_ppn = fp;
		}
		if (ppn != (ppnum_t)NULL) {
			if (is_64_bit) {
				fp = ml_phys_read_double_64(((((vm_offset_t)ppn) << PAGE_SHIFT)) | (fp & PAGE_MASK));
			} else {
				fp = ml_phys_read_word(((((vm_offset_t)ppn) << PAGE_SHIFT)) | (fp & PAGE_MASK));
			}
		} else {
			if (is_64_bit) {
				paniclog_append_noflush("%s\t  Could not read FP from frame at 0x%016llx\n", cur_marker, fp);
			} else {
				paniclog_append_noflush("%s\t  Could not read FP from frame at 0x%08x\n", cur_marker, (uint32_t)fp);
			}
			break;
		}

		if (is_64_bit) {
			paniclog_append_noflush("%s\t0x%016llx\n", cur_marker, lr);
		} else {
			paniclog_append_noflush("%s\t0x%08x\n", cur_marker, (uint32_t)lr);
		}
	} while ((++i < FP_MAX_NUM_TO_EVALUATE) && (fp != topfp));
}