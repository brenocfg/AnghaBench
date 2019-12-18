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
 int MAX_RECOG_ALTERNATIVES ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 char const* TREE_STRING_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int n_occurrences (char,char const*) ; 

__attribute__((used)) static bool
check_operand_nalternatives (tree outputs, tree inputs)
{
  if (outputs || inputs)
    {
      tree tmp = TREE_PURPOSE (outputs ? outputs : inputs);
      int nalternatives
	= n_occurrences (',', TREE_STRING_POINTER (TREE_VALUE (tmp)));
      tree next = inputs;

      if (nalternatives + 1 > MAX_RECOG_ALTERNATIVES)
	{
	  error ("too many alternatives in %<asm%>");
	  return false;
	}

      tmp = outputs;
      while (tmp)
	{
	  const char *constraint
	    = TREE_STRING_POINTER (TREE_VALUE (TREE_PURPOSE (tmp)));

	  if (n_occurrences (',', constraint) != nalternatives)
	    {
	      error ("operand constraints for %<asm%> differ "
		     "in number of alternatives");
	      return false;
	    }

	  if (TREE_CHAIN (tmp))
	    tmp = TREE_CHAIN (tmp);
	  else
	    tmp = next, next = 0;
	}
    }

  return true;
}