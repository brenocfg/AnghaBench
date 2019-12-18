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
struct TYPE_2__ {int /*<<< orphan*/  (* set_lazy_mode ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  paravirt_enter_lazy_mmu () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_1__ vmi_ops ; 

__attribute__((used)) static void vmi_enter_lazy_mmu(void)
{
	paravirt_enter_lazy_mmu();
	vmi_ops.set_lazy_mode(1);
}