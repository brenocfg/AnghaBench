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
struct TYPE_3__ {scalar_t__ imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NOT_IT ; 
 int /*<<< orphan*/  constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_it_mask ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_setend (void)
{
  constraint (current_it_mask, BAD_NOT_IT);
  if (inst.operands[0].imm)
    inst.instruction |= 0x8;
}