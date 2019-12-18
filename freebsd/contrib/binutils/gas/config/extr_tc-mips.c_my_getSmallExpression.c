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
typedef  int /*<<< orphan*/  expressionS ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;

/* Variables and functions */
 scalar_t__ HAVE_NEWABI ; 
 int /*<<< orphan*/  as_bad (char*) ; 
 char* expr_end ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  my_getExpression (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ parse_relocation (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_reloc_op_frag ; 

__attribute__((used)) static size_t
my_getSmallExpression (expressionS *ep, bfd_reloc_code_real_type *reloc,
		       char *str)
{
  bfd_reloc_code_real_type reversed_reloc[3];
  size_t reloc_index, i;
  int crux_depth, str_depth;
  char *crux;

  /* Search for the start of the main expression, recoding relocations
     in REVERSED_RELOC.  End the loop with CRUX pointing to the start
     of the main expression and with CRUX_DEPTH containing the number
     of open brackets at that point.  */
  reloc_index = -1;
  str_depth = 0;
  do
    {
      reloc_index++;
      crux = str;
      crux_depth = str_depth;

      /* Skip over whitespace and brackets, keeping count of the number
	 of brackets.  */
      while (*str == ' ' || *str == '\t' || *str == '(')
	if (*str++ == '(')
	  str_depth++;
    }
  while (*str == '%'
	 && reloc_index < (HAVE_NEWABI ? 3 : 1)
	 && parse_relocation (&str, &reversed_reloc[reloc_index]));

  my_getExpression (ep, crux);
  str = expr_end;

  /* Match every open bracket.  */
  while (crux_depth > 0 && (*str == ')' || *str == ' ' || *str == '\t'))
    if (*str++ == ')')
      crux_depth--;

  if (crux_depth > 0)
    as_bad ("unclosed '('");

  expr_end = str;

  if (reloc_index != 0)
    {
      prev_reloc_op_frag = frag_now;
      for (i = 0; i < reloc_index; i++)
	reloc[i] = reversed_reloc[reloc_index - 1 - i];
    }

  return reloc_index;
}