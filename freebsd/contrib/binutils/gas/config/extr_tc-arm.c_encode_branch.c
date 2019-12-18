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
struct TYPE_5__ {int type; int pc_rel; } ;
struct TYPE_6__ {TYPE_2__ reloc; TYPE_1__* operands; } ;
struct TYPE_4__ {scalar_t__ imm; scalar_t__ hasreloc; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_ARM_PLT32 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
encode_branch (int default_reloc)
{
  if (inst.operands[0].hasreloc)
    {
      constraint (inst.operands[0].imm != BFD_RELOC_ARM_PLT32,
		  _("the only suffix valid here is '(plt)'"));
      inst.reloc.type	= BFD_RELOC_ARM_PLT32;
    }
  else
    {
      inst.reloc.type = default_reloc;
    }
  inst.reloc.pc_rel = 1;
}