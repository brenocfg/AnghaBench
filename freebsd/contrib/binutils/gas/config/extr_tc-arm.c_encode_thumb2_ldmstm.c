#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_boolean ;
struct TYPE_2__ {int instruction; void* error; } ;

/* Variables and functions */
 int WRITE_BACK ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  as_warn (void*,...) ; 
 int ffs (unsigned int) ; 
 TYPE_1__ inst ; 

__attribute__((used)) static void
encode_thumb2_ldmstm (int base, unsigned mask, bfd_boolean writeback)
{
  bfd_boolean load;

  load = (inst.instruction & (1 << 20)) != 0;

  if (mask & (1 << 13))
    inst.error =  _("SP not allowed in register list");
  if (load)
    {
      if (mask & (1 << 14)
	  && mask & (1 << 15))
	inst.error = _("LR and PC should not both be in register list");

      if ((mask & (1 << base)) != 0
	  && writeback)
	as_warn (_("base register should not be in register list "
		   "when written back"));
    }
  else
    {
      if (mask & (1 << 15))
	inst.error = _("PC not allowed in register list");

      if (mask & (1 << base))
	as_warn (_("value stored for r%d is UNPREDICTABLE"), base);
    }

  if ((mask & (mask - 1)) == 0)
    {
      /* Single register transfers implemented as str/ldr.  */
      if (writeback)
	{
	  if (inst.instruction & (1 << 23))
	    inst.instruction = 0x00000b04; /* ia! -> [base], #4 */
	  else
	    inst.instruction = 0x00000d04; /* db! -> [base, #-4]! */
	}
      else
	{
	  if (inst.instruction & (1 << 23))
	    inst.instruction = 0x00800000; /* ia -> [base] */
	  else
	    inst.instruction = 0x00000c04; /* db -> [base, #-4] */
	}

      inst.instruction |= 0xf8400000;
      if (load)
	inst.instruction |= 0x00100000;

      mask = ffs(mask) - 1;
      mask <<= 12;
    }
  else if (writeback)
    inst.instruction |= WRITE_BACK;

  inst.instruction |= mask;
  inst.instruction |= base << 16;
}