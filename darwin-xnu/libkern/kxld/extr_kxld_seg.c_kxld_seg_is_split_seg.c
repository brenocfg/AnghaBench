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
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  KXLDSeg ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/  const*) ; 
 scalar_t__ isSplitKext ; 
 scalar_t__ kxld_seg_is_data_const_seg (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_seg_is_data_seg (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_seg_is_linkedit_seg (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_seg_is_llvm_cov_seg (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_seg_is_text_exec_seg (int /*<<< orphan*/  const*) ; 

boolean_t
kxld_seg_is_split_seg(const KXLDSeg *seg)
{
    boolean_t       result = FALSE;
    
    check(seg);
    if (isSplitKext) {
        if (kxld_seg_is_data_seg(seg) || kxld_seg_is_linkedit_seg(seg) ||
            kxld_seg_is_text_exec_seg(seg) || kxld_seg_is_data_const_seg(seg) ||
            kxld_seg_is_llvm_cov_seg(seg)) {
            result = TRUE;
        }
    }
    
    return result;
}