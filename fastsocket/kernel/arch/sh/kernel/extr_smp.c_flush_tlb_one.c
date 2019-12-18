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
struct flush_tlb_data {unsigned long addr1; unsigned long addr2; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_tlb_one_ipi ; 
 int /*<<< orphan*/  local_flush_tlb_one (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,void*,int) ; 

void flush_tlb_one(unsigned long asid, unsigned long vaddr)
{
	struct flush_tlb_data fd;

	fd.addr1 = asid;
	fd.addr2 = vaddr;

	smp_call_function(flush_tlb_one_ipi, (void *)&fd, 1);
	local_flush_tlb_one(asid, vaddr);
}