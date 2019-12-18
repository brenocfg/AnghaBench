#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ refers_to_regno_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
rs6000_output_load_multiple (rtx operands[3])
{
  /* We have to handle the case where the pseudo used to contain the address
     is assigned to one of the output registers.  */
  int i, j;
  int words = XVECLEN (operands[0], 0);
  rtx xop[10];

  if (XVECLEN (operands[0], 0) == 1)
    return "{l|lwz} %2,0(%1)";

  for (i = 0; i < words; i++)
    if (refers_to_regno_p (REGNO (operands[2]) + i,
			   REGNO (operands[2]) + i + 1, operands[1], 0))
      {
	if (i == words-1)
	  {
	    xop[0] = GEN_INT (4 * (words-1));
	    xop[1] = operands[1];
	    xop[2] = operands[2];
	    output_asm_insn ("{lsi|lswi} %2,%1,%0\n\t{l|lwz} %1,%0(%1)", xop);
	    return "";
	  }
	else if (i == 0)
	  {
	    xop[0] = GEN_INT (4 * (words-1));
	    xop[1] = operands[1];
	    xop[2] = gen_rtx_REG (SImode, REGNO (operands[2]) + 1);
	    output_asm_insn ("{cal %1,4(%1)|addi %1,%1,4}\n\t{lsi|lswi} %2,%1,%0\n\t{l|lwz} %1,-4(%1)", xop);
	    return "";
	  }
	else
	  {
	    for (j = 0; j < words; j++)
	      if (j != i)
		{
		  xop[0] = GEN_INT (j * 4);
		  xop[1] = operands[1];
		  xop[2] = gen_rtx_REG (SImode, REGNO (operands[2]) + j);
		  output_asm_insn ("{l|lwz} %2,%0(%1)", xop);
		}
	    xop[0] = GEN_INT (i * 4);
	    xop[1] = operands[1];
	    output_asm_insn ("{l|lwz} %1,%0(%1)", xop);
	    return "";
	  }
      }

  return "{lsi|lswi} %2,%1,%N0";
}