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
typedef  int /*<<< orphan*/  rtx ;
typedef  int HOST_WIDE_INT ;
typedef  int /*<<< orphan*/  CUMULATIVE_ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  current_function_args_info ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_args_info (tree arglist)
{
  int nwords = sizeof (CUMULATIVE_ARGS) / sizeof (int);
  int *word_ptr = (int *) &current_function_args_info;

  gcc_assert (sizeof (CUMULATIVE_ARGS) % sizeof (int) == 0);

  if (arglist != 0)
    {
      if (!host_integerp (TREE_VALUE (arglist), 0))
	error ("argument of %<__builtin_args_info%> must be constant");
      else
	{
	  HOST_WIDE_INT wordnum = tree_low_cst (TREE_VALUE (arglist), 0);

	  if (wordnum < 0 || wordnum >= nwords)
	    error ("argument of %<__builtin_args_info%> out of range");
	  else
	    return GEN_INT (word_ptr[wordnum]);
	}
    }
  else
    error ("missing argument in %<__builtin_args_info%>");

  return const0_rtx;
}