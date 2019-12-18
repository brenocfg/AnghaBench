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
struct TYPE_3__ {int reg; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  encode_arm_addr_mode_3 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 scalar_t__ move_or_literal_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_ldstv4 (void)
{
  inst.instruction |= inst.operands[0].reg << 12;
  if (!inst.operands[1].isreg)
    if (move_or_literal_pool (0, /*thumb_p=*/FALSE, /*mode_3=*/TRUE))
      return;
  encode_arm_addr_mode_3 (1, /*is_t=*/FALSE);
}