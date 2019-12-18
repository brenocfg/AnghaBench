#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {scalar_t__ index; struct TYPE_5__* aux; } ;

/* Variables and functions */
 TYPE_1__* BLOCK_FOR_INSN (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ INSN_DEPEND (scalar_t__) ; 
 scalar_t__ LOG_LINKS (scalar_t__) ; 
 scalar_t__ PFREE_CANDIDATE ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ haifa_classify_insn (scalar_t__) ; 

__attribute__((used)) static basic_block
earliest_block_with_similiar_load (basic_block last_block, rtx load_insn)
{
  rtx back_link;
  basic_block bb, earliest_block = NULL;

  for (back_link = LOG_LINKS (load_insn);
       back_link;
       back_link = XEXP (back_link, 1))
    {
      rtx insn1 = XEXP (back_link, 0);

      if (GET_MODE (back_link) == VOIDmode)
	{
	  /* Found a DEF-USE dependence (insn1, load_insn).  */
	  rtx fore_link;

	  for (fore_link = INSN_DEPEND (insn1);
	       fore_link;
	       fore_link = XEXP (fore_link, 1))
	    {
	      rtx insn2 = XEXP (fore_link, 0);
	      basic_block insn2_block = BLOCK_FOR_INSN (insn2);

	      if (GET_MODE (fore_link) == VOIDmode)
		{
		  if (earliest_block != NULL
		      && earliest_block->index < insn2_block->index)
		    continue;

		  /* Found a DEF-USE dependence (insn1, insn2).  */
		  if (haifa_classify_insn (insn2) != PFREE_CANDIDATE)
		    /* insn2 not guaranteed to be a 1 base reg load.  */
		    continue;

		  for (bb = last_block; bb; bb = bb->aux)
		    if (insn2_block == bb)
		      break;

		  if (!bb)
		    /* insn2 is the similar load.  */
		    earliest_block = insn2_block;
		}
	    }
	}
    }

  return earliest_block;
}