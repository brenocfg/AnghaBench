#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; scalar_t__ isreg; } ;

/* Variables and functions */
 int HI1 (int /*<<< orphan*/ ) ; 
 int LOW4 (int /*<<< orphan*/ ) ; 
 int NEON_ENC_IMMED (int) ; 
 int NEON_ENC_INTEGER (int) ; 
 int /*<<< orphan*/  NS_DD ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQ ; 
 TYPE_2__ inst ; 
 int neon_dp_fixup (int) ; 
 int /*<<< orphan*/  neon_move_immediate () ; 
 int neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_mvn (void)
{
  if (inst.operands[1].isreg)
    {
      enum neon_shape rs = neon_select_shape (NS_DD, NS_QQ, NS_NULL);
      
      inst.instruction = NEON_ENC_INTEGER (inst.instruction);
      inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
      inst.instruction |= HI1 (inst.operands[0].reg) << 22;
      inst.instruction |= LOW4 (inst.operands[1].reg);
      inst.instruction |= HI1 (inst.operands[1].reg) << 5;
      inst.instruction |= neon_quad (rs) << 6;
    }
  else
    {
      inst.instruction = NEON_ENC_IMMED (inst.instruction);
      neon_move_immediate ();
    }

  inst.instruction = neon_dp_fixup (inst.instruction);
}