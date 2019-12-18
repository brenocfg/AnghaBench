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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 unsigned int SECTION_WRITE ; 
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  default_elf_asm_named_section (char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
i386_solaris_elf_named_section (const char *name, unsigned int flags,
				tree decl)
{
  /* With Binutils 2.15, the "@unwind" marker must be specified on
     every occurrence of the ".eh_frame" section, not just the first
     one.  */
  if (TARGET_64BIT
      && strcmp (name, ".eh_frame") == 0)
    {
      fprintf (asm_out_file, "\t.section\t%s,\"%s\",@unwind\n", name,
	       flags & SECTION_WRITE ? "aw" : "a");
      return;
    }
  default_elf_asm_named_section (name, flags, decl);
}