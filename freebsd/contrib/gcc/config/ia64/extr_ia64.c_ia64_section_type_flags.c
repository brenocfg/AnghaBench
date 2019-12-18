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
 unsigned int SECTION_SMALL ; 
 unsigned int default_section_type_flags (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static unsigned int
ia64_section_type_flags (tree decl, const char *name, int reloc)
{
  unsigned int flags = 0;

  if (strcmp (name, ".sdata") == 0
      || strncmp (name, ".sdata.", 7) == 0
      || strncmp (name, ".gnu.linkonce.s.", 16) == 0
      || strncmp (name, ".sdata2.", 8) == 0
      || strncmp (name, ".gnu.linkonce.s2.", 17) == 0
      || strcmp (name, ".sbss") == 0
      || strncmp (name, ".sbss.", 6) == 0
      || strncmp (name, ".gnu.linkonce.sb.", 17) == 0)
    flags = SECTION_SMALL;

  flags |= default_section_type_flags (decl, name, reloc);
  return flags;
}