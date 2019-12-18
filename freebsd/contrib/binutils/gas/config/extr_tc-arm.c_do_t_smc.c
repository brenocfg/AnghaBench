#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int X_add_number; scalar_t__ X_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; TYPE_1__ exp; } ;
struct TYPE_6__ {unsigned int instruction; TYPE_2__ reloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
do_t_smc (void)
{
  unsigned int value = inst.reloc.exp.X_add_number;
  constraint (inst.reloc.exp.X_op != O_constant,
	      _("expression too complex"));
  inst.reloc.type = BFD_RELOC_UNUSED;
  inst.instruction |= (value & 0xf000) >> 12;
  inst.instruction |= (value & 0x0ff0);
  inst.instruction |= (value & 0x000f) << 16;
}