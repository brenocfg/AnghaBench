#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* insn; int /*<<< orphan*/  buffer; int /*<<< orphan*/  fields; } ;
typedef  TYPE_2__ mep_insn ;
struct TYPE_9__ {TYPE_1__* base; } ;
struct TYPE_7__ {int num; } ;

/* Variables and functions */
 int CGEN_FIELDS_BITSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CGEN_INSN_ATTR_VALUE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_INSN_VLIW32_NO_MATCHING_NOP ; 
 int MEP_INSN_BEQZ ; 
 int MEP_INSN_BNEZ ; 
 int MEP_INSN_BSR12 ; 
 int MEP_INSN_COP_P (TYPE_5__*) ; 
 int /*<<< orphan*/  as_bad (char*,...) ; 
 int /*<<< orphan*/  as_fatal (char*) ; 
 int /*<<< orphan*/  gas_cgen_cpu_desc ; 
 int /*<<< orphan*/  gas_cgen_save_fixups (int) ; 
 int /*<<< orphan*/  gas_cgen_swap_fixups (int /*<<< orphan*/ ) ; 
 void* mep_cgen_assemble_insn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mep_save_insn (TYPE_2__) ; 
 int num_insns_saved ; 
 TYPE_2__* saved_insns ; 

__attribute__((used)) static void
mep_check_parallel32_scheduling (void)
{
  int insn0iscopro, insn1iscopro, insn0length, insn1length;

  /* More than two instructions means that either someone is referring to
     an internally parallel core or an internally parallel coprocessor,
     neither of which are supported at this time.  */
  if ( num_insns_saved > 2 )
    as_fatal("Internally paralled cores and coprocessors not supported.");

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
      /* Check some of the attributes of the first insn.  */
      insn1iscopro = MEP_INSN_COP_P (saved_insns[1].insn);
      insn1length = CGEN_FIELDS_BITSIZE (& saved_insns[1].fields);

      if ((insn0iscopro && !insn1iscopro)
          || (insn1iscopro && !insn0iscopro))
	{
          /* We have one core and one copro insn.  If their sizes
             add up to 32, then the combination is valid.  */
	  if (insn0length + insn1length == 32)
	    return;
          else
	    as_bad ("core and copro insn lengths must total 32 bits.");
	}
      else
        as_bad ("vliw group must consist of 1 core and 1 copro insn."); 
    }
  else
    {
      /* If we arrive here, we have one saved instruction.  There are a
	 number of possible cases:

	 1.  The instruction is a 32 bit core or coprocessor insn and
             can be executed by itself.  Valid.

         2.  The instrucion is a core instruction for which a cop nop
             exists.  In this case, insert the cop nop into the saved
             insn array after the core insn and return.  Valid.

         3.  The instruction is a coprocessor insn for which a core nop
             exists.  In this case, move the coprocessor insn to the
             second element of the array and put the nop in the first
	     element then return.  Valid.

         4. The instruction is a core or coprocessor instruction for
            which there is no matching coprocessor or core nop to use
	    to form a valid vliw insn combination.  In this case, we
	    we have to abort.  */

      if (insn0length > 32)
	as_fatal ("Cannot use 48- or 64-bit insns with a 32 bit datapath.");

      if (insn0length == 32)
	return;

      /* Insn is smaller than datapath.  If there are no matching
         nops for this insn, then terminate assembly.  */
      if (CGEN_INSN_ATTR_VALUE (saved_insns[0].insn,
                                CGEN_INSN_VLIW32_NO_MATCHING_NOP))
	as_fatal ("No valid nop.");

      /* At this point we know that we have a single 16-bit insn that has 
	 a matching nop.  We have to assemble it and put it into the saved 
         insn and fixup chain arrays. */

      if (insn0iscopro)
	{
          char *errmsg;
          mep_insn insn;
         
          /* Move the insn and it's fixups to the second element of the
             saved insns arrary and insert a 16 bit core nope into the
             first element. */
             insn.insn = mep_cgen_assemble_insn (gas_cgen_cpu_desc, "nop",
                                                 &insn.fields, insn.buffer,
                                                 &errmsg);
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
              gas_cgen_swap_fixups (0);
              gas_cgen_save_fixups (1);
	}
      else
	{
          char * errmsg;
          mep_insn insn;
	  int insn_num = saved_insns[0].insn->base->num;

	  /* Use 32 bit branches and skip the nop.  */
	  if (insn_num == MEP_INSN_BSR12
	      || insn_num == MEP_INSN_BEQZ
	      || insn_num == MEP_INSN_BNEZ)
	    return;

          /* Insert a 16-bit coprocessor nop.  Note that at the time */
          /* this was done, no 16-bit coprocessor nop was defined.   */
	  insn.insn = mep_cgen_assemble_insn (gas_cgen_cpu_desc, "cpnop16",
					      &insn.fields, insn.buffer,
					      &errmsg);
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