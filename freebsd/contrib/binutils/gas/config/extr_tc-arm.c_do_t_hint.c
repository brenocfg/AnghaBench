#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size_req; int /*<<< orphan*/  instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  THUMB_OP16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THUMB_OP32 (int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_hint (void)
{
  if (unified_syntax && inst.size_req == 4)
    inst.instruction = THUMB_OP32 (inst.instruction);
  else
    inst.instruction = THUMB_OP16 (inst.instruction);
}