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
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; } ;

/* Variables and functions */
 int BFD_RELOC_ARM_CP_OFF_IMM_S2 ; 
 int BFD_RELOC_ARM_T32_CP_OFF_IMM_S2 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  encode_arm_cp_address (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ inst ; 
 scalar_t__ thumb_mode ; 

__attribute__((used)) static void
do_iwmmxt_wldstbh (void)
{
  int reloc;
  inst.instruction |= inst.operands[0].reg << 12;
  if (thumb_mode)
    reloc = BFD_RELOC_ARM_T32_CP_OFF_IMM_S2;
  else
    reloc = BFD_RELOC_ARM_CP_OFF_IMM_S2;
  encode_arm_cp_address (1, TRUE, FALSE, reloc);
}