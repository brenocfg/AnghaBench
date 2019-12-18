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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 char* REGISTER_PREFIX ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 
 char** reg_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 
 int store_multiple_sequence (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

const char *
emit_stm_seq (rtx *operands, int nops)
{
  int regs[4];
  int base_reg;
  HOST_WIDE_INT offset;
  char buf[100];
  int i;

  switch (store_multiple_sequence (operands, nops, regs, &base_reg, &offset))
    {
    case 1:
      strcpy (buf, "stm%?ia\t");
      break;

    case 2:
      strcpy (buf, "stm%?ib\t");
      break;

    case 3:
      strcpy (buf, "stm%?da\t");
      break;

    case 4:
      strcpy (buf, "stm%?db\t");
      break;

    default:
      gcc_unreachable ();
    }

  sprintf (buf + strlen (buf), "%s%s, {%s%s", REGISTER_PREFIX,
	   reg_names[base_reg], REGISTER_PREFIX, reg_names[regs[0]]);

  for (i = 1; i < nops; i++)
    sprintf (buf + strlen (buf), ", %s%s", REGISTER_PREFIX,
	     reg_names[regs[i]]);

  strcat (buf, "}\t%@ phole stm");

  output_asm_insn (buf, operands);
  return "";
}