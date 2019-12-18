#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_9__ {int /*<<< orphan*/  stack_adjust; } ;
struct TYPE_6__ {int /*<<< orphan*/  stack_adjust; } ;
struct TYPE_10__ {int n_mos; TYPE_4__ out; TYPE_3__* mos; TYPE_1__ in; } ;
struct TYPE_7__ {int /*<<< orphan*/  loc; scalar_t__ adjust; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MO_ADJUST ; 
 scalar_t__ MO_CALL ; 
 TYPE_5__* VTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_stack_reference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bb_stack_adjust_offset (basic_block bb)
{
  HOST_WIDE_INT offset;
  int i;

  offset = VTI (bb)->in.stack_adjust;
  for (i = 0; i < VTI (bb)->n_mos; i++)
    {
      if (VTI (bb)->mos[i].type == MO_ADJUST)
	offset += VTI (bb)->mos[i].u.adjust;
      else if (VTI (bb)->mos[i].type != MO_CALL)
	{
	  if (MEM_P (VTI (bb)->mos[i].u.loc))
	    {
	      VTI (bb)->mos[i].u.loc
		= adjust_stack_reference (VTI (bb)->mos[i].u.loc, -offset);
	    }
	}
    }
  VTI (bb)->out.stack_adjust = offset;
}