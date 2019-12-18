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
typedef  int /*<<< orphan*/  mips16_little_breakpoint ;
typedef  int /*<<< orphan*/  mips16_big_breakpoint ;
typedef  int /*<<< orphan*/  little_breakpoint ;
typedef  int /*<<< orphan*/  big_breakpoint ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ pc_is_mips16 (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  target_shortname ; 
 int /*<<< orphan*/  unmake_mips16_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const unsigned char *
mips_breakpoint_from_pc (CORE_ADDR *pcptr, int *lenptr)
{
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    {
      if (pc_is_mips16 (*pcptr))
	{
	  static unsigned char mips16_big_breakpoint[] = { 0xe8, 0xa5 };
	  *pcptr = unmake_mips16_addr (*pcptr);
	  *lenptr = sizeof (mips16_big_breakpoint);
	  return mips16_big_breakpoint;
	}
      else
	{
	  /* The IDT board uses an unusual breakpoint value, and
	     sometimes gets confused when it sees the usual MIPS
	     breakpoint instruction.  */
	  static unsigned char big_breakpoint[] = { 0, 0x5, 0, 0xd };
	  static unsigned char pmon_big_breakpoint[] = { 0, 0, 0, 0xd };
	  static unsigned char idt_big_breakpoint[] = { 0, 0, 0x0a, 0xd };

	  *lenptr = sizeof (big_breakpoint);

	  if (strcmp (target_shortname, "mips") == 0)
	    return idt_big_breakpoint;
	  else if (strcmp (target_shortname, "ddb") == 0
		   || strcmp (target_shortname, "pmon") == 0
		   || strcmp (target_shortname, "lsi") == 0)
	    return pmon_big_breakpoint;
	  else
	    return big_breakpoint;
	}
    }
  else
    {
      if (pc_is_mips16 (*pcptr))
	{
	  static unsigned char mips16_little_breakpoint[] = { 0xa5, 0xe8 };
	  *pcptr = unmake_mips16_addr (*pcptr);
	  *lenptr = sizeof (mips16_little_breakpoint);
	  return mips16_little_breakpoint;
	}
      else
	{
	  static unsigned char little_breakpoint[] = { 0xd, 0, 0x5, 0 };
	  static unsigned char pmon_little_breakpoint[] = { 0xd, 0, 0, 0 };
	  static unsigned char idt_little_breakpoint[] = { 0xd, 0x0a, 0, 0 };

	  *lenptr = sizeof (little_breakpoint);

	  if (strcmp (target_shortname, "mips") == 0)
	    return idt_little_breakpoint;
	  else if (strcmp (target_shortname, "ddb") == 0
		   || strcmp (target_shortname, "pmon") == 0
		   || strcmp (target_shortname, "lsi") == 0)
	    return pmon_little_breakpoint;
	  else
	    return little_breakpoint;
	}
    }
}