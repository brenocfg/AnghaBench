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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 char* REGISTER_PREFIX ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int load_multiple_sequence (int /*<<< orphan*/ *,int,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 
 char** reg_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

const char *
emit_ldm_seq (rtx *operands, int nops)
{
  int regs[4];
  int base_reg;
  HOST_WIDE_INT offset;
  char buf[100];
  int i;

  switch (load_multiple_sequence (operands, nops, regs, &base_reg, &offset))
    {
    case 1:
      strcpy (buf, "ldm%?ia\t");
      break;

    case 2:
      strcpy (buf, "ldm%?ib\t");
      break;

    case 3:
      strcpy (buf, "ldm%?da\t");
      break;

    case 4:
      strcpy (buf, "ldm%?db\t");
      break;

    case 5:
      if (offset >= 0)
	sprintf (buf, "add%%?\t%s%s, %s%s, #%ld", REGISTER_PREFIX,
		 reg_names[regs[0]], REGISTER_PREFIX, reg_names[base_reg],
		 (long) offset);
      else
	sprintf (buf, "sub%%?\t%s%s, %s%s, #%ld", REGISTER_PREFIX,
		 reg_names[regs[0]], REGISTER_PREFIX, reg_names[base_reg],
		 (long) -offset);
      output_asm_insn (buf, operands);
      base_reg = regs[0];
      strcpy (buf, "ldm%?ia\t");
      break;

    default:
      gcc_unreachable ();
    }

  sprintf (buf + strlen (buf), "%s%s, {%s%s", REGISTER_PREFIX,
	   reg_names[base_reg], REGISTER_PREFIX, reg_names[regs[0]]);

  for (i = 1; i < nops; i++)
    sprintf (buf + strlen (buf), ", %s%s", REGISTER_PREFIX,
	     reg_names[regs[i]]);

  strcat (buf, "}\t%@ phole ldm");

  output_asm_insn (buf, operands);
  return "";
}