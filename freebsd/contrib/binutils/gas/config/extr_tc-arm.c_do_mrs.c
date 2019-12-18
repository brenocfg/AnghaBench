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
struct TYPE_3__ {int imm; int reg; } ;

/* Variables and functions */
 int PSR_c ; 
 int PSR_f ; 
 int PSR_s ; 
 int PSR_x ; 
 int SPSR_BIT ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 scalar_t__ do_vfp_nsyn_mrs () ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_mrs (void)
{
  if (do_vfp_nsyn_mrs () == SUCCESS)
    return;

  /* mrs only accepts CPSR/SPSR/CPSR_all/SPSR_all.  */
  constraint ((inst.operands[1].imm & (PSR_c|PSR_x|PSR_s|PSR_f))
	      != (PSR_c|PSR_f),
	      _("'CPSR' or 'SPSR' expected"));
  inst.instruction |= inst.operands[0].reg << 12;
  inst.instruction |= (inst.operands[1].imm & SPSR_BIT);
}