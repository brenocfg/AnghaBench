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
struct TYPE_6__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
struct TYPE_7__ {TYPE_2__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_1__* operands; TYPE_3__ reloc; } ;
struct TYPE_5__ {int postind; int writeback; int reg; scalar_t__ preind; } ;

/* Variables and functions */
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_arm_addr_mode_3 (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ inst ; 

__attribute__((used)) static void
do_ldsttv4 (void)
{
  /* ldrt/strt always use post-indexed addressing.  Turn [Rn] into [Rn]! and
     reject [Rn,...].  */
  if (inst.operands[1].preind)
    {
      constraint (inst.reloc.exp.X_op != O_constant ||
		  inst.reloc.exp.X_add_number != 0,
		  _("this instruction requires a post-indexed address"));

      inst.operands[1].preind = 0;
      inst.operands[1].postind = 1;
      inst.operands[1].writeback = 1;
    }
  inst.instruction |= inst.operands[0].reg << 12;
  encode_arm_addr_mode_3 (1, /*is_t=*/TRUE);
}