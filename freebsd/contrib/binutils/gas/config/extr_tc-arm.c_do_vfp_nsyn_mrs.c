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
struct TYPE_4__ {TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; scalar_t__ isvec; } ;

/* Variables and functions */
 int FAIL ; 
 int SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 

__attribute__((used)) static int
do_vfp_nsyn_mrs (void)
{
  if (inst.operands[0].isvec)
    {
      if (inst.operands[1].reg != 1)
        first_error (_("operand 1 must be FPSCR"));
      memset (&inst.operands[0], '\0', sizeof (inst.operands[0]));
      memset (&inst.operands[1], '\0', sizeof (inst.operands[1]));
      do_vfp_nsyn_opcode ("fmstat");
    }
  else if (inst.operands[1].isvec)
    do_vfp_nsyn_opcode ("fmrx");
  else
    return FAIL;
    
  return SUCCESS;
}