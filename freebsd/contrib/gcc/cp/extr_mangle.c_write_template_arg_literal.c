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
#define  CONST_DECL 130 
 int /*<<< orphan*/  const DECL_INITIAL (int /*<<< orphan*/  const) ; 
#define  INTEGER_CST 129 
#define  REAL_CST 128 
 int TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  integer_onep (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_integer_cst (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_real_cst (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_template_arg_literal (const tree value)
{
  write_char ('L');
  write_type (TREE_TYPE (value));

  switch (TREE_CODE (value))
    {
    case CONST_DECL:
      write_integer_cst (DECL_INITIAL (value));
      break;

    case INTEGER_CST:
      gcc_assert (!same_type_p (TREE_TYPE (value), boolean_type_node)
		  || integer_zerop (value) || integer_onep (value));
      write_integer_cst (value);
      break;

    case REAL_CST:
      write_real_cst (value);
      break;

    default:
      gcc_unreachable ();
    }

  write_char ('E');
}