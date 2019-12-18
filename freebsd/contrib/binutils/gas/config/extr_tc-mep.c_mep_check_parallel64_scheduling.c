#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buffer; void* insn; int /*<<< orphan*/  fields; } ;
typedef  TYPE_1__ mep_insn ;

/* Variables and functions */
 int CGEN_FIELDS_BITSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CGEN_INSN_ATTR_VALUE (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_INSN_VLIW64_NO_MATCHING_NOP ; 
 int MEP_INSN_COP_P (void*) ; 
 int /*<<< orphan*/  as_bad (char*,...) ; 
 int /*<<< orphan*/  as_fatal (char*) ; 
 int /*<<< orphan*/  gas_cgen_cpu_desc ; 
 int /*<<< orphan*/  gas_cgen_save_fixups (int) ; 
 int /*<<< orphan*/  gas_cgen_swap_fixups (int /*<<< orphan*/ ) ; 
 void* mep_cgen_assemble_insn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  mep_save_insn (TYPE_1__) ; 
 int num_insns_saved ; 
 TYPE_1__* saved_insns ; 

__attribute__((used)) static void
mep_check_parallel64_scheduling (void)
{
  int insn0iscopro, insn1iscopro, insn0length, insn1length;

  /* More than two instructions means that someone is referring to an
     internally parallel core or an internally parallel coprocessor.  */
  /* These are not currently supported.  */
  if (num_insns_saved > 2)
    as_fatal ("Internally parallel cores of coprocessors not supported.");

  /* If there are no insns saved, that's ok.  Just return.  This will
     happen when mep_process_saved_insns is called when the end of the
     source file is reached and there are no insns left to be processed.  */
  if (num_insns_saved == 0)
    return;

  /* Check some of the attributes of the first insn.  */
  insn0iscopro = MEP_INSN_COP_P (saved_insns[0].insn);
  insn0length = CGEN_FIELDS_BITSIZE (& saved_insns[0].fields);

  if (num_insns_saved == 2)
    {
      /* Check some of the attributes of the first insn. */
      insn1iscopro = MEP_INSN_COP_P (saved_insns[1].insn);
      insn1length = CGEN_FIELDS_BITSIZE (& saved_insns[1].fields);

      if ((insn0iscopro && !insn1iscopro)
	  || (insn1iscopro && !insn0iscopro))
	{
	  /* We have one core and one copro insn.  If their sizes
	     add up to 64, then the combination is valid.  */
	  if (insn0length + insn1length == 64)
            return;
	  else
            as_bad ("core and copro insn lengths must total 64 bits.");
	}
      else
        as_bad ("vliw group must consist of 1 core and 1 copro insn.");
    }
  else
    {
      /* If we arrive here, we have one saved instruction.  There are a
	 number of possible cases:

         1.  The instruction is a 64 bit coprocessor insn and can be
             executed by itself.  Valid.

         2.  The instrucion is a core instruction for which a cop nop
             exists.  In this case, insert the cop nop into the saved
             insn array after the core insn and return.  Valid.

         3.  The instruction is a coprocessor insn for which a core nop
             exists.  In this case, move the coprocessor insn to the
             second element of the array and put the nop in the first
             element then return.  Valid.

         4.  The instruction is a core or coprocessor instruction for
             which there is no matching coprocessor or core nop to use
             to form a valid vliw insn combination.  In this case, we
	     we have to abort.  */

      /* If the insn is 64 bits long, it can run alone.  The size check
	 is done indepependantly of whether the insn is core or copro
	 in case 64 bit coprocessor insns are added later.  */
      if (insn0length == 64)
        return;

      /* Insn is smaller than datapath.  If there are no matching
	 nops for this insn, then terminate assembly.  */
      if (CGEN_INSN_ATTR_VALUE (saved_insns[0].insn,
				CGEN_INSN_VLIW64_NO_MATCHING_NOP))
	as_fatal ("No valid nop.");

      if (insn0iscopro)
	{
	  char *errmsg;
	  mep_insn insn;
          int i;

          /* Initialize the insn buffer.  */
          for (i = 0; i < 64; i++)
             insn.buffer[i] = '\0';

	  /* We have a coprocessor insn.  At this point in time there
	     are is 32-bit core nop.  There is only a 16-bit core
	     nop.  The idea is to allow for a relatively arbitrary
	     coprocessor to be specified.  We aren't looking at
	     trying to cover future changes in the core at this time
	     since it is assumed that the core will remain fairly
	     static.  If there ever are 32 or 48 bit core nops added,
	     they will require entries below.  */

	  if (insn0length == 48)
	    {
	      /* Move the insn and fixups to the second element of the
		 arrays then assemble and insert a 16 bit core nop.  */
	      insn.insn = mep_cgen_assemble_insn (gas_cgen_cpu_desc, "nop",
						  & insn.fields, insn.buffer,
						  & errmsg);
	    }
          else
            {
              /* If this is reached, then we have a single coprocessor
                 insn that is not 48 bits long, but for which the assembler
                 thinks there is a matching core nop.  If a 32-bit core
                 nop has been added, then make the necessary changes and
                 handle its assembly and insertion here.  Otherwise,
                 go figure out why either:
              
                 1. The assembler thinks that there is a 32-bit core nop
                    to match a 32-bit coprocessor insn, or
                 2. The assembler thinks that there is a 48-bit core nop
                    to match a 16-bit coprocessor insn.  */

              as_fatal ("Assembler expects a non-existent core nop.");
            }

	 if (!insn.insn)
	   {
	     as_bad ("%s", errmsg);
	     return;
	   }

         /* Move the insn in element 0 to element 1 and insert the
            nop into element 0.  Move the fixups in element 0 to
            element 1 and save the current fixups to element 0. 
	    Really there aren't any fixups at this point because we're
	    inserting a nop but we might as well be general so that
	    if there's ever a need to insert a general insn, we'll
	    have an example. */

         saved_insns[1] = saved_insns[0];
         saved_insns[0] = insn;
         num_insns_saved++;
         gas_cgen_swap_fixups(0);
         gas_cgen_save_fixups(1);

	}
      else
	{
	  char * errmsg;
	  mep_insn insn;
          int i;

          /* Initialize the insn buffer */
          for (i = 0; i < 64; i++)
             insn.buffer[i] = '\0';

	  /* We have a core insn.  We have to handle all possible nop
	     lengths.  If a coprocessor doesn't have a nop of a certain
	     length but there exists core insns that when combined with
	      a nop of that length would fill the datapath, those core
	      insns will be flagged with the VLIW_NO_CORRESPONDING_NOP
	      attribute.  That will ensure that when used in a way that
	      requires a nop to be inserted, assembly will terminate
	      before reaching this section of code.  This guarantees
	      that cases below which would result in the attempted
	      insertion of nop that doesn't exist will never be entered.  */
	  if (insn0length == 16)
	    {
	      /* Insert 48 bit coprocessor nop.          */
	      /* Assemble it and put it into the arrays. */
	      insn.insn = mep_cgen_assemble_insn (gas_cgen_cpu_desc, "cpnop48",
						  &insn.fields, insn.buffer,
						  &errmsg);
	    }
	  else if (insn0length == 32)
	    {
	      /* Insert 32 bit coprocessor nop. */
	      insn.insn = mep_cgen_assemble_insn (gas_cgen_cpu_desc, "cpnop32",
						  &insn.fields, insn.buffer,
						  &errmsg);
	    }
	  else if (insn0length == 48)
	    {
	      /* Insert 16 bit coprocessor nop. */
	      insn.insn = mep_cgen_assemble_insn (gas_cgen_cpu_desc, "cpnop16",
						  &insn.fields, insn.buffer,
						  &errmsg);
	    }
	  else
	    /* Core insn has an invalid length.  Something has gone wrong. */
	    as_fatal ("Core insn has invalid length!  Something is wrong!");

	  if (!insn.insn)
	    {
	      as_bad ("%s", errmsg);
	      return;
	    }

	  /* Now put the insn and fixups into the arrays.  */
	  mep_save_insn (insn);
	}
    }
}