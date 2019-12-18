#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pgdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_SET_PTE ; 
 int /*<<< orphan*/  lazy_hcall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__ lguest_data ; 

__attribute__((used)) static void lguest_flush_tlb_single(unsigned long addr)
{
	/* Simply set it to zero: if it was not, it will fault back in. */
	lazy_hcall3(LHCALL_SET_PTE, lguest_data.pgdir, addr, 0);
}