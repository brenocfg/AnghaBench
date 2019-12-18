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

/* Variables and functions */
 scalar_t__ ISPRINT (scalar_t__) ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 scalar_t__* input_line_pointer ; 
 scalar_t__* is_end_of_line ; 
 int /*<<< orphan*/  know (scalar_t__) ; 

void
demand_empty_rest_of_line (void)
{
  SKIP_WHITESPACE ();
  if (is_end_of_line[(unsigned char) *input_line_pointer])
    input_line_pointer++;
  else
    {
      if (ISPRINT (*input_line_pointer))
	as_bad (_("junk at end of line, first unrecognized character is `%c'"),
		 *input_line_pointer);
      else
	as_bad (_("junk at end of line, first unrecognized character valued 0x%x"),
		 *input_line_pointer);
      ignore_rest_of_line ();
    }
  
  /* Return pointing just after end-of-line.  */
  know (is_end_of_line[(unsigned char) input_line_pointer[-1]]);
}