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

/* Variables and functions */
 size_t PR_REG (unsigned int) ; 
 int /*<<< orphan*/  asm_out_file ; 
 scalar_t__* call_used_regs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 

void
emit_safe_across_calls (void)
{
  unsigned int rs, re;
  int out_state;

  rs = 1;
  out_state = 0;
  while (1)
    {
      while (rs < 64 && call_used_regs[PR_REG (rs)])
	rs++;
      if (rs >= 64)
	break;
      for (re = rs + 1; re < 64 && ! call_used_regs[PR_REG (re)]; re++)
	continue;
      if (out_state == 0)
	{
	  fputs ("\t.pred.safe_across_calls ", asm_out_file);
	  out_state = 1;
	}
      else
	fputc (',', asm_out_file);
      if (re == rs + 1)
	fprintf (asm_out_file, "p%u", rs);
      else
	fprintf (asm_out_file, "p%u-p%u", rs, re - 1);
      rs = re + 1;
    }
  if (out_state)
    fputc ('\n', asm_out_file);
}