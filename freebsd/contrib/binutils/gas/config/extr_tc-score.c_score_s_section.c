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
 int SEC_CODE ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  obj_elf_section (int) ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdoutput ; 

__attribute__((used)) static void
score_s_section (int ignore)
{
  obj_elf_section (ignore);
  if ((bfd_get_section_flags (stdoutput, now_seg) & SEC_CODE) != 0)
    record_alignment (now_seg, 2);

}