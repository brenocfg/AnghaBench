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

/* Variables and functions */
 int /*<<< orphan*/  IVector ; 
 int /*<<< orphan*/  SBIH ; 
 int /*<<< orphan*/  SBIHOld ; 
 int /*<<< orphan*/  SBIHRM ; 
 int /*<<< orphan*/  SBIHRMOld ; 
 int /*<<< orphan*/  _go32_dpmi_free_iret_wrapper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_free_real_mode_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_protected_mode_interrupt_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_real_mode_interrupt_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ResetVectors(void)
{
 _go32_dpmi_set_protected_mode_interrupt_vector(IVector,&SBIHOld);
 _go32_dpmi_free_iret_wrapper(&SBIH);
 _go32_dpmi_set_real_mode_interrupt_vector(IVector,&SBIHRMOld);
 _go32_dpmi_free_real_mode_callback(&SBIHRM);
}