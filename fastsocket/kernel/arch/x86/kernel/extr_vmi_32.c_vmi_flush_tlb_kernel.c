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
struct TYPE_2__ {int /*<<< orphan*/  (* _flush_tlb ) (int) ;} ;

/* Variables and functions */
 int VMI_FLUSH_GLOBAL ; 
 int VMI_FLUSH_TLB ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_1__ vmi_ops ; 

__attribute__((used)) static void vmi_flush_tlb_kernel(void)
{
	vmi_ops._flush_tlb(VMI_FLUSH_TLB | VMI_FLUSH_GLOBAL);
}