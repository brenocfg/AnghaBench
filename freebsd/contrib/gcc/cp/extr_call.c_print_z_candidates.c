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
typedef  int /*<<< orphan*/  tree ;
struct z_candidate {struct z_candidate* next; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 scalar_t__ alloca (size_t) ; 
 scalar_t__ equal_functions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gcc_gettext_width (char const*) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  print_z_candidate (char const*,struct z_candidate*) ; 

__attribute__((used)) static void
print_z_candidates (struct z_candidate *candidates)
{
  const char *str;
  struct z_candidate *cand1;
  struct z_candidate **cand2;

  /* There may be duplicates in the set of candidates.  We put off
     checking this condition as long as possible, since we have no way
     to eliminate duplicates from a set of functions in less than n^2
     time.  Now we are about to emit an error message, so it is more
     permissible to go slowly.  */
  for (cand1 = candidates; cand1; cand1 = cand1->next)
    {
      tree fn = cand1->fn;
      /* Skip builtin candidates and conversion functions.  */
      if (TREE_CODE (fn) != FUNCTION_DECL)
	continue;
      cand2 = &cand1->next;
      while (*cand2)
	{
	  if (TREE_CODE ((*cand2)->fn) == FUNCTION_DECL
	      && equal_functions (fn, (*cand2)->fn))
	    *cand2 = (*cand2)->next;
	  else
	    cand2 = &(*cand2)->next;
	}
    }

  if (!candidates)
    return;

  str = _("candidates are:");
  print_z_candidate (str, candidates);
  if (candidates->next)
    {
      /* Indent successive candidates by the width of the translation
	 of the above string.  */
      size_t len = gcc_gettext_width (str) + 1;
      char *spaces = (char *) alloca (len);
      memset (spaces, ' ', len-1);
      spaces[len - 1] = '\0';

      candidates = candidates->next;
      do
	{
	  print_z_candidate (spaces, candidates);
	  candidates = candidates->next;
	}
      while (candidates);
    }
}