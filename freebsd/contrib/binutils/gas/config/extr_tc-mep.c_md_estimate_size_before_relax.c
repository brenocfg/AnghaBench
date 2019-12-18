#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ segT ;
struct TYPE_9__ {TYPE_2__* insn; } ;
struct TYPE_10__ {int fr_subtype; TYPE_3__ fr_cgen; int /*<<< orphan*/  fr_symbol; } ;
typedef  TYPE_4__ fragS ;
struct TYPE_11__ {int insn_for_extern; int insn; int growth; } ;
struct TYPE_8__ {TYPE_1__* base; } ;
struct TYPE_7__ {int num; } ;

/* Variables and functions */
#define  MEP_INSN_BEQZ 130 
#define  MEP_INSN_BNEZ 129 
#define  MEP_INSN_BSR12 128 
 scalar_t__ MEP_VLIW ; 
 int /*<<< orphan*/  MEP_VLIW64 ; 
 int SEC_MEP_VLIW ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ ) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,scalar_t__) ; 
 void* insn_to_subtype (int) ; 
 int /*<<< orphan*/  stdoutput ; 
 TYPE_5__* subtype_mappings ; 

int
md_estimate_size_before_relax (fragS * fragP, segT segment)
{
  if (fragP->fr_subtype == 1)
    fragP->fr_subtype = insn_to_subtype (fragP->fr_cgen.insn->base->num);

  if (S_GET_SEGMENT (fragP->fr_symbol) != segment)
    {
      int new_insn;

      new_insn = subtype_mappings[fragP->fr_subtype].insn_for_extern;
      fragP->fr_subtype = insn_to_subtype (new_insn);
    }

  if (MEP_VLIW && ! MEP_VLIW64
      && (bfd_get_section_flags (stdoutput, segment) & SEC_MEP_VLIW))
    {
      /* Use 32 bit branches for vliw32 so the vliw word is not split.  */
      switch (fragP->fr_cgen.insn->base->num)
	{
	case MEP_INSN_BSR12:
	  fragP->fr_subtype = insn_to_subtype 
	    (subtype_mappings[fragP->fr_subtype].insn_for_extern);
	  break;
	case MEP_INSN_BEQZ:
	  fragP->fr_subtype ++;
	  break;
	case MEP_INSN_BNEZ:
	  fragP->fr_subtype ++;
	  break;
	}
    }

  if (fragP->fr_cgen.insn->base
      && fragP->fr_cgen.insn->base->num
         != subtype_mappings[fragP->fr_subtype].insn)
    {
      int new_insn= subtype_mappings[fragP->fr_subtype].insn;
      if (new_insn != -1)
	{
	  fragP->fr_cgen.insn = (fragP->fr_cgen.insn
				 - fragP->fr_cgen.insn->base->num
				 + new_insn);
	}
    }

  return subtype_mappings[fragP->fr_subtype].growth;
}