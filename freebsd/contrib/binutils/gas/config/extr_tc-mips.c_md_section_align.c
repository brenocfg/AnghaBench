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
typedef  int valueT ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 scalar_t__ IS_ELF ; 
 int /*<<< orphan*/  TARGET_OS ; 
 int bfd_get_section_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

valueT
md_section_align (asection *seg, valueT addr)
{
  int align = bfd_get_section_alignment (stdoutput, seg);

  if (IS_ELF)
    {
      /* We don't need to align ELF sections to the full alignment.
	 However, Irix 5 may prefer that we align them at least to a 16
	 byte boundary.  We don't bother to align the sections if we
	 are targeted for an embedded system.  */
      if (strcmp (TARGET_OS, "elf") == 0)
        return addr;
      if (align > 4)
        align = 4;
    }

  return ((addr + (1 << align) - 1) & (-1 << align));
}