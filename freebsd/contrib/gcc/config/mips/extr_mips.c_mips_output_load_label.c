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
#define  ABI_64 129 
#define  ABI_N32 128 
 scalar_t__ DImode ; 
 int /*<<< orphan*/  ISA_HAS_LOAD_DELAY ; 
 scalar_t__ Pmode ; 
 scalar_t__ TARGET_EXPLICIT_RELOCS ; 
 int mips_abi ; 

const char *
mips_output_load_label (void)
{
  if (TARGET_EXPLICIT_RELOCS)
    switch (mips_abi)
      {
      case ABI_N32:
	return "%[lw\t%@,%%got_page(%0)(%+)\n\taddiu\t%@,%@,%%got_ofst(%0)";

      case ABI_64:
	return "%[ld\t%@,%%got_page(%0)(%+)\n\tdaddiu\t%@,%@,%%got_ofst(%0)";

      default:
	if (ISA_HAS_LOAD_DELAY)
	  return "%[lw\t%@,%%got(%0)(%+)%#\n\taddiu\t%@,%@,%%lo(%0)";
	return "%[lw\t%@,%%got(%0)(%+)\n\taddiu\t%@,%@,%%lo(%0)";
      }
  else
    {
      if (Pmode == DImode)
	return "%[dla\t%@,%0";
      else
	return "%[la\t%@,%0";
    }
}