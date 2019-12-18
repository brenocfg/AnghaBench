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
 scalar_t__ ISDIGIT (unsigned char) ; 
 void* alloca (int) ; 
 int asm_noperands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_operand_ok (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  constrain_operands (int) ; 
 int /*<<< orphan*/  decode_asm_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_insn_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ which_alternative ; 

int
check_asm_operands (rtx x)
{
  int noperands;
  rtx *operands;
  const char **constraints;
  int i;

  /* Post-reload, be more strict with things.  */
  if (reload_completed)
    {
      /* ??? Doh!  We've not got the wrapping insn.  Cook one up.  */
      extract_insn (make_insn_raw (x));
      constrain_operands (1);
      return which_alternative >= 0;
    }

  noperands = asm_noperands (x);
  if (noperands < 0)
    return 0;
  if (noperands == 0)
    return 1;

  operands = alloca (noperands * sizeof (rtx));
  constraints = alloca (noperands * sizeof (char *));

  decode_asm_operands (x, operands, NULL, constraints, NULL);

  for (i = 0; i < noperands; i++)
    {
      const char *c = constraints[i];
      if (c[0] == '%')
	c++;
      if (ISDIGIT ((unsigned char) c[0]) && c[1] == '\0')
	c = constraints[c[0] - '0'];

      if (! asm_operand_ok (operands[i], c))
	return 0;
    }

  return 1;
}