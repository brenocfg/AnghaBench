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
typedef  int /*<<< orphan*/  u64 ;
struct thash_data {int /*<<< orphan*/  itir; int /*<<< orphan*/  page_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TLB ; 
 struct thash_data* __vtr_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_vcpu ; 
 int /*<<< orphan*/  thash_vhpt_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 guest_vhpt_lookup(u64 iha, u64 *pte)
{
	u64 ret;
	struct thash_data *data;

	data = __vtr_lookup(current_vcpu, iha, D_TLB);
	if (data != NULL)
		thash_vhpt_insert(current_vcpu, data->page_flags,
			data->itir, iha, D_TLB);

	asm volatile ("rsm psr.ic|psr.i;;"
			"srlz.d;;"
			"ld8.s r9=[%1];;"
			"tnat.nz p6,p7=r9;;"
			"(p6) mov %0=1;"
			"(p6) mov r9=r0;"
			"(p7) extr.u r9=r9,0,53;;"
			"(p7) mov %0=r0;"
			"(p7) st8 [%2]=r9;;"
			"ssm psr.ic;;"
			"srlz.d;;"
			"ssm psr.i;;"
			"srlz.d;;"
			: "=r"(ret) : "r"(iha), "r"(pte):"memory");

	return ret;
}