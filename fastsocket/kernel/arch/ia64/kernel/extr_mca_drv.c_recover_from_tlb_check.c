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
struct TYPE_3__ {int /*<<< orphan*/  check_info; } ;
typedef  TYPE_1__ sal_log_mod_error_info_t ;
typedef  int /*<<< orphan*/  peidx_table_t ;
struct TYPE_4__ {scalar_t__ op; scalar_t__ itc; scalar_t__ dtc; scalar_t__ itr; } ;
typedef  TYPE_2__ pal_tlb_check_info_t ;

/* Variables and functions */
 scalar_t__ PAL_TLB_CHECK_OP_PURGE ; 
 int fatal_mca (char*) ; 
 int mca_recovered (char*) ; 
 scalar_t__ peidx_tlb_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
recover_from_tlb_check(peidx_table_t *peidx)
{
	sal_log_mod_error_info_t *smei;
	pal_tlb_check_info_t *ptci;

	smei = (sal_log_mod_error_info_t *)peidx_tlb_check(peidx, 0);
	ptci = (pal_tlb_check_info_t *)&(smei->check_info);

	/*
	 * Look for signature of a duplicate TLB DTC entry, which is
	 * a SW bug and always fatal.
	 */
	if (ptci->op == PAL_TLB_CHECK_OP_PURGE
	    && !(ptci->itr || ptci->dtc || ptci->itc))
		return fatal_mca("Duplicate TLB entry");

	return mca_recovered("TLB check recovered");
}