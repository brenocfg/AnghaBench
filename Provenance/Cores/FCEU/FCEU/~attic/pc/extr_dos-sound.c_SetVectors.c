#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pm_offset; int /*<<< orphan*/  pm_selector; } ;
struct TYPE_7__ {int pm_offset; int /*<<< orphan*/  pm_selector; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVector ; 
 TYPE_2__ SBIH ; 
 int /*<<< orphan*/  SBIHOld ; 
 TYPE_1__ SBIHRM ; 
 int /*<<< orphan*/  SBIHRMOld ; 
 int /*<<< orphan*/  SBIHRMRegs ; 
 scalar_t__ SBIRQHandler ; 
 int /*<<< orphan*/  _go32_dpmi_allocate_iret_wrapper (TYPE_2__*) ; 
 int /*<<< orphan*/  _go32_dpmi_allocate_real_mode_callback_iret (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_get_protected_mode_interrupt_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_get_real_mode_interrupt_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_protected_mode_interrupt_vector (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  _go32_dpmi_set_real_mode_interrupt_vector (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _my_cs () ; 

__attribute__((used)) static int SetVectors(void)
{
 SBIH.pm_offset=SBIHRM.pm_offset=(int)SBIRQHandler;
 SBIH.pm_selector=SBIHRM.pm_selector=_my_cs();

 /* Get and set real mode interrupt vector.  */
 _go32_dpmi_get_real_mode_interrupt_vector(IVector,&SBIHRMOld);
 _go32_dpmi_allocate_real_mode_callback_iret(&SBIHRM, &SBIHRMRegs);
 _go32_dpmi_set_real_mode_interrupt_vector(IVector,&SBIHRM);  

 /* Get and set protected mode interrupt vector. */
 _go32_dpmi_get_protected_mode_interrupt_vector(IVector,&SBIHOld);
 _go32_dpmi_allocate_iret_wrapper(&SBIH);
 _go32_dpmi_set_protected_mode_interrupt_vector(IVector,&SBIH); 

 return(1);
}