#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  segname; } ;
typedef  TYPE_1__ KXLDSeg ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  check (TYPE_1__ const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

boolean_t
kxld_seg_is_llvm_cov_seg(const KXLDSeg *seg)
{
    boolean_t       result = FALSE;

    check(seg);
    result = !strncmp(seg->segname, "__LLVM_COV", sizeof(seg->segname));

    return result;
}