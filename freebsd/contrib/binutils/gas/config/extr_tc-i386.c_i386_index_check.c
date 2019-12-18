#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* start; TYPE_1__* end; } ;
struct TYPE_11__ {scalar_t__* prefix; int* types; scalar_t__ log2_scale_factor; int prefixes; TYPE_4__* index_reg; TYPE_3__* base_reg; } ;
struct TYPE_10__ {unsigned int reg_type; int reg_num; } ;
struct TYPE_9__ {int reg_type; int reg_num; } ;
struct TYPE_8__ {int cpu_flags; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__* operand_types; } ;

/* Variables and functions */
 size_t ADDR_PREFIX ; 
 scalar_t__ ADDR_PREFIX_OPCODE ; 
 int Acc ; 
 scalar_t__ AnyMem ; 
 unsigned int BaseIndex ; 
 size_t CODE_16BIT ; 
 size_t CODE_64BIT ; 
 int CpuSVME ; 
 int Disp ; 
 int Disp16 ; 
 int Disp32 ; 
 unsigned int Reg16 ; 
 unsigned int Reg32 ; 
 unsigned int Reg64 ; 
 unsigned int RegRex ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_6__* current_templates ; 
 size_t flag_code ; 
 int /*<<< orphan*/ * flag_code_names ; 
 TYPE_5__ i ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t this_operand ; 

__attribute__((used)) static int
i386_index_check (const char *operand_string)
{
  int ok;
#if INFER_ADDR_PREFIX
  int fudged = 0;

 tryprefix:
#endif
  ok = 1;
  if ((current_templates->start->cpu_flags & CpuSVME)
      && current_templates->end[-1].operand_types[0] == AnyMem)
    {
      /* Memory operands of SVME insns are special in that they only allow
	 rAX as their memory address and ignore any segment override.  */
      unsigned RegXX;

      /* SKINIT is even more restrictive: it always requires EAX.  */
      if (strcmp (current_templates->start->name, "skinit") == 0)
	RegXX = Reg32;
      else if (flag_code == CODE_64BIT)
	RegXX = i.prefix[ADDR_PREFIX] == 0 ? Reg64 : Reg32;
      else
	RegXX = ((flag_code == CODE_16BIT) ^ (i.prefix[ADDR_PREFIX] != 0)
		 ? Reg16
		 : Reg32);
      if (!i.base_reg
	  || !(i.base_reg->reg_type & Acc)
	  || !(i.base_reg->reg_type & RegXX)
	  || i.index_reg
	  || (i.types[0] & Disp))
	ok = 0;
    }
  else if (flag_code == CODE_64BIT)
    {
      unsigned RegXX = (i.prefix[ADDR_PREFIX] == 0 ? Reg64 : Reg32);

      if ((i.base_reg
	   && ((i.base_reg->reg_type & RegXX) == 0)
	   && (i.base_reg->reg_type != BaseIndex
	       || i.index_reg))
	  || (i.index_reg
	      && ((i.index_reg->reg_type & (RegXX | BaseIndex))
		  != (RegXX | BaseIndex))))
	ok = 0;
    }
  else
    {
      if ((flag_code == CODE_16BIT) ^ (i.prefix[ADDR_PREFIX] != 0))
	{
	  /* 16bit checks.  */
	  if ((i.base_reg
	       && ((i.base_reg->reg_type & (Reg16 | BaseIndex | RegRex))
		   != (Reg16 | BaseIndex)))
	      || (i.index_reg
		  && (((i.index_reg->reg_type & (Reg16 | BaseIndex))
		       != (Reg16 | BaseIndex))
		      || !(i.base_reg
			   && i.base_reg->reg_num < 6
			   && i.index_reg->reg_num >= 6
			   && i.log2_scale_factor == 0))))
	    ok = 0;
	}
      else
	{
	  /* 32bit checks.  */
	  if ((i.base_reg
	       && (i.base_reg->reg_type & (Reg32 | RegRex)) != Reg32)
	      || (i.index_reg
		  && ((i.index_reg->reg_type & (Reg32 | BaseIndex | RegRex))
		      != (Reg32 | BaseIndex))))
	    ok = 0;
	}
    }
  if (!ok)
    {
#if INFER_ADDR_PREFIX
      if (i.prefix[ADDR_PREFIX] == 0)
	{
	  i.prefix[ADDR_PREFIX] = ADDR_PREFIX_OPCODE;
	  i.prefixes += 1;
	  /* Change the size of any displacement too.  At most one of
	     Disp16 or Disp32 is set.
	     FIXME.  There doesn't seem to be any real need for separate
	     Disp16 and Disp32 flags.  The same goes for Imm16 and Imm32.
	     Removing them would probably clean up the code quite a lot.  */
	  if (flag_code != CODE_64BIT
	      && (i.types[this_operand] & (Disp16 | Disp32)))
	    i.types[this_operand] ^= (Disp16 | Disp32);
	  fudged = 1;
	  goto tryprefix;
	}
      if (fudged)
	as_bad (_("`%s' is not a valid base/index expression"),
		operand_string);
      else
#endif
	as_bad (_("`%s' is not a valid %s bit base/index expression"),
		operand_string,
		flag_code_names[flag_code]);
    }
  return ok;
}