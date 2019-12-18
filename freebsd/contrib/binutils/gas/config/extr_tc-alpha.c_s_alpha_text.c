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
 int alpha_auto_align_on ; 
 scalar_t__ alpha_current_align ; 
 int /*<<< orphan*/ * alpha_insn_label ; 
 int /*<<< orphan*/  obj_elf_text (int) ; 
 int /*<<< orphan*/  s_text (int) ; 

__attribute__((used)) static void
s_alpha_text (int i)

{
#ifdef OBJ_ELF
  obj_elf_text (i);
#else
  s_text (i);
#endif
  alpha_insn_label = NULL;
  alpha_auto_align_on = 1;
  alpha_current_align = 0;
}