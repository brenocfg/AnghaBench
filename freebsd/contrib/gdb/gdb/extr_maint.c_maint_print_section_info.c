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
typedef  int /*<<< orphan*/  flagword ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  local_hex_string_custom (unsigned long,char*) ; 
 int /*<<< orphan*/  paddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_bfd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 

__attribute__((used)) static void
maint_print_section_info (const char *name, flagword flags, 
			  CORE_ADDR addr, CORE_ADDR endaddr, 
			  unsigned long filepos)
{
  /* FIXME-32x64: Need print_address_numeric with field width.  */
  printf_filtered ("    0x%s", paddr (addr));
  printf_filtered ("->0x%s", paddr (endaddr));
  printf_filtered (" at %s",
		   local_hex_string_custom ((unsigned long) filepos, "08l"));
  printf_filtered (": %s", name);
  print_bfd_flags (flags);
  printf_filtered ("\n");
}