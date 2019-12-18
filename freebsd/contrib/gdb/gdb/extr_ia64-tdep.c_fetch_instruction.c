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
typedef  int /*<<< orphan*/  instruction_type ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int BUNDLE_LEN ; 
 int /*<<< orphan*/  L ; 
 int SLOT_MULTIPLIER ; 
 long long extract_bit_field (char*,int /*<<< orphan*/ ,int) ; 
 long long slotN_contents (char*,int) ; 
 int target_read_memory (int,char*,int) ; 
 int /*<<< orphan*/ ** template_encoding_table ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static CORE_ADDR
fetch_instruction (CORE_ADDR addr, instruction_type *it, long long *instr)
{
  char bundle[BUNDLE_LEN];
  int slotnum = (int) (addr & 0x0f) / SLOT_MULTIPLIER;
  long long template;
  int val;

  /* Warn about slot numbers greater than 2.  We used to generate
     an error here on the assumption that the user entered an invalid
     address.  But, sometimes GDB itself requests an invalid address.
     This can (easily) happen when execution stops in a function for
     which there are no symbols.  The prologue scanner will attempt to
     find the beginning of the function - if the nearest symbol
     happens to not be aligned on a bundle boundary (16 bytes), the
     resulting starting address will cause GDB to think that the slot
     number is too large.

     So we warn about it and set the slot number to zero.  It is
     not necessarily a fatal condition, particularly if debugging
     at the assembly language level.  */
  if (slotnum > 2)
    {
      warning ("Can't fetch instructions for slot numbers greater than 2.\n"
	       "Using slot 0 instead");
      slotnum = 0;
    }

  addr &= ~0x0f;

  val = target_read_memory (addr, bundle, BUNDLE_LEN);

  if (val != 0)
    return 0;

  *instr = slotN_contents (bundle, slotnum);
  template = extract_bit_field (bundle, 0, 5);
  *it = template_encoding_table[(int)template][slotnum];

  if (slotnum == 2 || (slotnum == 1 && *it == L))
    addr += 16;
  else
    addr += (slotnum + 1) * SLOT_MULTIPLIER;

  return addr;
}