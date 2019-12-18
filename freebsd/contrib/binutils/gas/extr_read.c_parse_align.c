#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int offsetT ;
struct TYPE_3__ {scalar_t__ X_op; int /*<<< orphan*/  X_unsigned; } ;
typedef  TYPE_1__ expressionS ;
typedef  int addressT ;

/* Variables and functions */
 scalar_t__ O_absent ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int get_absolute_expr (TYPE_1__*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 

offsetT
parse_align (int align_bytes)
{
  expressionS exp;
  addressT align;

  SKIP_WHITESPACE ();
  if (*input_line_pointer != ',')
    {
    no_align:
      as_bad (_("expected alignment after size"));
      ignore_rest_of_line ();
      return -1;
    }

  input_line_pointer++;
  SKIP_WHITESPACE ();

  align = get_absolute_expr (&exp);
  if (exp.X_op == O_absent)
    goto no_align;

  if (!exp.X_unsigned)
    {
      as_warn (_("alignment negative; 0 assumed"));
      align = 0;
    }

  if (align_bytes && align != 0)
    {
      /* convert to a power of 2 alignment */
      unsigned int alignp2 = 0;
      while ((align & 1) == 0)
	align >>= 1, ++alignp2;
      if (align != 1)
	{
	  as_bad (_("alignment not a power of 2"));
	  ignore_rest_of_line ();
	  return -1;
	}
      align = alignp2;
    }
  return align;
}