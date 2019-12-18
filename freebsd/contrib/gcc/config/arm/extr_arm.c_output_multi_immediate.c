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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  output_asm_insn (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
output_multi_immediate (rtx *operands, const char *instr1, const char *instr2,
			int immed_op, HOST_WIDE_INT n)
{
#if HOST_BITS_PER_WIDE_INT > 32
  n &= 0xffffffff;
#endif

  if (n == 0)
    {
      /* Quick and easy output.  */
      operands[immed_op] = const0_rtx;
      output_asm_insn (instr1, operands);
    }
  else
    {
      int i;
      const char * instr = instr1;

      /* Note that n is never zero here (which would give no output).  */
      for (i = 0; i < 32; i += 2)
	{
	  if (n & (3 << i))
	    {
	      operands[immed_op] = GEN_INT (n & (255 << i));
	      output_asm_insn (instr, operands);
	      instr = instr2;
	      i += 6;
	    }
	}
    }

  return "";
}