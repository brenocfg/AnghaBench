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
typedef  enum reload_type { ____Placeholder_reload_type } reload_type ;
struct TYPE_2__ {int when_needed; int opnum; } ;

/* Variables and functions */
#define  RELOAD_FOR_INPADDR_ADDRESS 138 
#define  RELOAD_FOR_INPUT 137 
#define  RELOAD_FOR_INPUT_ADDRESS 136 
#define  RELOAD_FOR_INSN 135 
#define  RELOAD_FOR_OPADDR_ADDR 134 
#define  RELOAD_FOR_OPERAND_ADDRESS 133 
#define  RELOAD_FOR_OTHER_ADDRESS 132 
#define  RELOAD_FOR_OUTADDR_ADDRESS 131 
#define  RELOAD_FOR_OUTPUT 130 
#define  RELOAD_FOR_OUTPUT_ADDRESS 129 
#define  RELOAD_OTHER 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_1__* rld ; 

__attribute__((used)) static int
reloads_conflict (int r1, int r2)
{
  enum reload_type r1_type = rld[r1].when_needed;
  enum reload_type r2_type = rld[r2].when_needed;
  int r1_opnum = rld[r1].opnum;
  int r2_opnum = rld[r2].opnum;

  /* RELOAD_OTHER conflicts with everything.  */
  if (r2_type == RELOAD_OTHER)
    return 1;

  /* Otherwise, check conflicts differently for each type.  */

  switch (r1_type)
    {
    case RELOAD_FOR_INPUT:
      return (r2_type == RELOAD_FOR_INSN
	      || r2_type == RELOAD_FOR_OPERAND_ADDRESS
	      || r2_type == RELOAD_FOR_OPADDR_ADDR
	      || r2_type == RELOAD_FOR_INPUT
	      || ((r2_type == RELOAD_FOR_INPUT_ADDRESS
		   || r2_type == RELOAD_FOR_INPADDR_ADDRESS)
		  && r2_opnum > r1_opnum));

    case RELOAD_FOR_INPUT_ADDRESS:
      return ((r2_type == RELOAD_FOR_INPUT_ADDRESS && r1_opnum == r2_opnum)
	      || (r2_type == RELOAD_FOR_INPUT && r2_opnum < r1_opnum));

    case RELOAD_FOR_INPADDR_ADDRESS:
      return ((r2_type == RELOAD_FOR_INPADDR_ADDRESS && r1_opnum == r2_opnum)
	      || (r2_type == RELOAD_FOR_INPUT && r2_opnum < r1_opnum));

    case RELOAD_FOR_OUTPUT_ADDRESS:
      return ((r2_type == RELOAD_FOR_OUTPUT_ADDRESS && r2_opnum == r1_opnum)
	      || (r2_type == RELOAD_FOR_OUTPUT && r2_opnum <= r1_opnum));

    case RELOAD_FOR_OUTADDR_ADDRESS:
      return ((r2_type == RELOAD_FOR_OUTADDR_ADDRESS && r2_opnum == r1_opnum)
	      || (r2_type == RELOAD_FOR_OUTPUT && r2_opnum <= r1_opnum));

    case RELOAD_FOR_OPERAND_ADDRESS:
      return (r2_type == RELOAD_FOR_INPUT || r2_type == RELOAD_FOR_INSN
	      || r2_type == RELOAD_FOR_OPERAND_ADDRESS);

    case RELOAD_FOR_OPADDR_ADDR:
      return (r2_type == RELOAD_FOR_INPUT
	      || r2_type == RELOAD_FOR_OPADDR_ADDR);

    case RELOAD_FOR_OUTPUT:
      return (r2_type == RELOAD_FOR_INSN || r2_type == RELOAD_FOR_OUTPUT
	      || ((r2_type == RELOAD_FOR_OUTPUT_ADDRESS
		   || r2_type == RELOAD_FOR_OUTADDR_ADDRESS)
		  && r2_opnum >= r1_opnum));

    case RELOAD_FOR_INSN:
      return (r2_type == RELOAD_FOR_INPUT || r2_type == RELOAD_FOR_OUTPUT
	      || r2_type == RELOAD_FOR_INSN
	      || r2_type == RELOAD_FOR_OPERAND_ADDRESS);

    case RELOAD_FOR_OTHER_ADDRESS:
      return r2_type == RELOAD_FOR_OTHER_ADDRESS;

    case RELOAD_OTHER:
      return 1;

    default:
      gcc_unreachable ();
    }
}