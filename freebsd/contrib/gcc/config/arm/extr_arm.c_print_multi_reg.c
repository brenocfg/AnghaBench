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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 unsigned int LAST_ARM_REGNUM ; 
 int TRUE ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_multi_reg (FILE *stream, const char *instr, unsigned reg,
		 unsigned long mask)
{
  unsigned i;
  bool not_first = FALSE;

  fputc ('\t', stream);
  asm_fprintf (stream, instr, reg);
  fputs (", {", stream);

  for (i = 0; i <= LAST_ARM_REGNUM; i++)
    if (mask & (1 << i))
      {
	if (not_first)
	  fprintf (stream, ", ");

	asm_fprintf (stream, "%r", i);
	not_first = TRUE;
      }

  fprintf (stream, "}\n");
}