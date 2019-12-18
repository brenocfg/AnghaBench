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
 int FIRST_VFP_REGNUM ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

const char *
vfp_output_fstmx (rtx * operands)
{
  char pattern[100];
  int p;
  int base;
  int i;

  strcpy (pattern, "fstmfdx\t%m0!, {%P1");
  p = strlen (pattern);

  gcc_assert (GET_CODE (operands[1]) == REG);

  base = (REGNO (operands[1]) - FIRST_VFP_REGNUM) / 2;
  for (i = 1; i < XVECLEN (operands[2], 0); i++)
    {
      p += sprintf (&pattern[p], ", d%d", base + i);
    }
  strcpy (&pattern[p], "}");

  output_asm_insn (pattern, operands);
  return "";
}