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

/* Variables and functions */
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_VEC ; 
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,int) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_template_arg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_template_args (tree args)
{
  int i;
  int length = TREE_VEC_LENGTH (args);

  MANGLE_TRACE_TREE ("template-args", args);

  write_char ('I');

  gcc_assert (length > 0);

  if (TREE_CODE (TREE_VEC_ELT (args, 0)) == TREE_VEC)
    {
      /* We have nested template args.  We want the innermost template
	 argument list.  */
      args = TREE_VEC_ELT (args, length - 1);
      length = TREE_VEC_LENGTH (args);
    }
  for (i = 0; i < length; ++i)
    write_template_arg (TREE_VEC_ELT (args, i));

  write_char ('E');
}