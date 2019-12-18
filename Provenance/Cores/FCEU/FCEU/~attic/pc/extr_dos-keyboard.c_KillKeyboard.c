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
 int /*<<< orphan*/  KBI ; 
 int /*<<< orphan*/  KBIBack ; 
 int /*<<< orphan*/  KBIBackRM ; 
 int /*<<< orphan*/  KBIRM ; 
 int /*<<< orphan*/  _go32_dpmi_free_iret_wrapper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_free_real_mode_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_protected_mode_interrupt_vector (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _go32_dpmi_set_real_mode_interrupt_vector (int,int /*<<< orphan*/ *) ; 
 scalar_t__ initdone ; 

void KillKeyboard(void)
{
 if(initdone)
 {
  _go32_dpmi_set_protected_mode_interrupt_vector(9,&KBIBack);
  _go32_dpmi_free_iret_wrapper(&KBI);

  _go32_dpmi_set_real_mode_interrupt_vector(9,&KBIBackRM);
  _go32_dpmi_free_real_mode_callback(&KBIRM);
  initdone=0;
 }
}