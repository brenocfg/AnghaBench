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
struct attr_desc {int dummy; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  AND ; 
 scalar_t__ COND ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  NOT ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ attr_rtx (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ eliminate_known_true (scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ false_rtx ; 
 scalar_t__ insert_right_side (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ true_rtx ; 
 int /*<<< orphan*/  write_attr_value (struct attr_desc*,scalar_t__) ; 
 int /*<<< orphan*/  write_indent (int) ; 
 int /*<<< orphan*/  write_test_expr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_attr_set (struct attr_desc *attr, int indent, rtx value,
		const char *prefix, const char *suffix, rtx known_true,
		int insn_code, int insn_index)
{
  if (GET_CODE (value) == COND)
    {
      /* Assume the default value will be the default of the COND unless we
	 find an always true expression.  */
      rtx default_val = XEXP (value, 1);
      rtx our_known_true = known_true;
      rtx newexp;
      int first_if = 1;
      int i;

      for (i = 0; i < XVECLEN (value, 0); i += 2)
	{
	  rtx testexp;
	  rtx inner_true;

	  testexp = eliminate_known_true (our_known_true,
					  XVECEXP (value, 0, i),
					  insn_code, insn_index);
	  newexp = attr_rtx (NOT, testexp);
	  newexp = insert_right_side (AND, our_known_true, newexp,
				      insn_code, insn_index);

	  /* If the test expression is always true or if the next `known_true'
	     expression is always false, this is the last case, so break
	     out and let this value be the `else' case.  */
	  if (testexp == true_rtx || newexp == false_rtx)
	    {
	      default_val = XVECEXP (value, 0, i + 1);
	      break;
	    }

	  /* Compute the expression to pass to our recursive call as being
	     known true.  */
	  inner_true = insert_right_side (AND, our_known_true,
					  testexp, insn_code, insn_index);

	  /* If this is always false, skip it.  */
	  if (inner_true == false_rtx)
	    continue;

	  write_indent (indent);
	  printf ("%sif ", first_if ? "" : "else ");
	  first_if = 0;
	  write_test_expr (testexp, 0);
	  printf ("\n");
	  write_indent (indent + 2);
	  printf ("{\n");

	  write_attr_set (attr, indent + 4,
			  XVECEXP (value, 0, i + 1), prefix, suffix,
			  inner_true, insn_code, insn_index);
	  write_indent (indent + 2);
	  printf ("}\n");
	  our_known_true = newexp;
	}

      if (! first_if)
	{
	  write_indent (indent);
	  printf ("else\n");
	  write_indent (indent + 2);
	  printf ("{\n");
	}

      write_attr_set (attr, first_if ? indent : indent + 4, default_val,
		      prefix, suffix, our_known_true, insn_code, insn_index);

      if (! first_if)
	{
	  write_indent (indent + 2);
	  printf ("}\n");
	}
    }
  else
    {
      write_indent (indent);
      printf ("%s ", prefix);
      write_attr_value (attr, value);
      printf ("%s\n", suffix);
    }
}