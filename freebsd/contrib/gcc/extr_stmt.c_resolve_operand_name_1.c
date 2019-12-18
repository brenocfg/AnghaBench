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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 char* TREE_STRING_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static char *
resolve_operand_name_1 (char *p, tree outputs, tree inputs)
{
  char *q;
  int op;
  tree t;
  size_t len;

  /* Collect the operand name.  */
  q = strchr (p, ']');
  if (!q)
    {
      error ("missing close brace for named operand");
      return strchr (p, '\0');
    }
  len = q - p - 1;

  /* Resolve the name to a number.  */
  for (op = 0, t = outputs; t ; t = TREE_CHAIN (t), op++)
    {
      tree name = TREE_PURPOSE (TREE_PURPOSE (t));
      if (name)
	{
	  const char *c = TREE_STRING_POINTER (name);
	  if (strncmp (c, p + 1, len) == 0 && c[len] == '\0')
	    goto found;
	}
    }
  for (t = inputs; t ; t = TREE_CHAIN (t), op++)
    {
      tree name = TREE_PURPOSE (TREE_PURPOSE (t));
      if (name)
	{
	  const char *c = TREE_STRING_POINTER (name);
	  if (strncmp (c, p + 1, len) == 0 && c[len] == '\0')
	    goto found;
	}
    }

  *q = '\0';
  error ("undefined named operand %qs", p + 1);
  op = 0;
 found:

  /* Replace the name with the number.  Unfortunately, not all libraries
     get the return value of sprintf correct, so search for the end of the
     generated string by hand.  */
  sprintf (p, "%d", op);
  p = strchr (p, '\0');

  /* Verify the no extra buffer space assumption.  */
  gcc_assert (p <= q);

  /* Shift the rest of the buffer down to fill the gap.  */
  memmove (p, q + 1, strlen (q + 1) + 1);

  return p;
}