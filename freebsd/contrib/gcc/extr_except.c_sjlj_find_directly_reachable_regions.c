#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct sjlj_lp_info {int directly_reachable; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_2__ throw; } ;
struct eh_region {scalar_t__ type; size_t region_number; struct eh_region* outer; TYPE_3__ u; } ;
typedef  scalar_t__ rtx ;
typedef  enum reachable_code { ____Placeholder_reachable_code } reachable_code ;
struct TYPE_8__ {TYPE_1__* eh; } ;
struct TYPE_5__ {int /*<<< orphan*/  region_array; } ;

/* Variables and functions */
 scalar_t__ ERT_THROW ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  REG_EH_REGION ; 
 int RNL_CAUGHT ; 
 int RNL_MAYBE_CAUGHT ; 
 int RNL_NOT_CAUGHT ; 
 struct eh_region* VEC_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__* cfun ; 
 int /*<<< orphan*/  eh_region ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int reachable_next_level (struct eh_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
sjlj_find_directly_reachable_regions (struct sjlj_lp_info *lp_info)
{
  rtx insn;
  bool found_one = false;

  for (insn = get_insns (); insn ; insn = NEXT_INSN (insn))
    {
      struct eh_region *region;
      enum reachable_code rc;
      tree type_thrown;
      rtx note;

      if (! INSN_P (insn))
	continue;

      note = find_reg_note (insn, REG_EH_REGION, NULL_RTX);
      if (!note || INTVAL (XEXP (note, 0)) <= 0)
	continue;

      region = VEC_index (eh_region, cfun->eh->region_array, INTVAL (XEXP (note, 0)));

      type_thrown = NULL_TREE;
      if (region->type == ERT_THROW)
	{
	  type_thrown = region->u.throw.type;
	  region = region->outer;
	}

      /* Find the first containing region that might handle the exception.
	 That's the landing pad to which we will transfer control.  */
      rc = RNL_NOT_CAUGHT;
      for (; region; region = region->outer)
	{
	  rc = reachable_next_level (region, type_thrown, NULL);
	  if (rc != RNL_NOT_CAUGHT)
	    break;
	}
      if (rc == RNL_MAYBE_CAUGHT || rc == RNL_CAUGHT)
	{
	  lp_info[region->region_number].directly_reachable = 1;
	  found_one = true;
	}
    }

  return found_one;
}