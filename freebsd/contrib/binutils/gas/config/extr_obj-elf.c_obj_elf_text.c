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
 int /*<<< orphan*/  md_elf_section_change_hook () ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 int /*<<< orphan*/  previous_section ; 
 int /*<<< orphan*/  previous_subsection ; 
 int /*<<< orphan*/  s_text (int) ; 

void
obj_elf_text (int i)
{
#ifdef md_flush_pending_output
  md_flush_pending_output ();
#endif

  previous_section = now_seg;
  previous_subsection = now_subseg;
  s_text (i);

#ifdef md_elf_section_change_hook
  md_elf_section_change_hook ();
#endif
}