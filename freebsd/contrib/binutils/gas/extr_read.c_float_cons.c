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
struct TYPE_3__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ ISALPHA (char) ; 
 int MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 char* frag_more (int) ; 
 int hex_float (int,char*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 scalar_t__ is_it_end_of_statement () ; 
 int /*<<< orphan*/  know (int) ; 
 char* md_atof (int,char*,int*) ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  need_pass_2 ; 

void
float_cons (/* Clobbers input_line-pointer, checks end-of-line.  */
	    register int float_type	/* 'f':.ffloat ... 'F':.float ...  */)
{
  register char *p;
  int length;			/* Number of chars in an object.  */
  register char *err;		/* Error from scanning floating literal.  */
  char temp[MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT];

  if (is_it_end_of_statement ())
    {
      demand_empty_rest_of_line ();
      return;
    }

#ifdef md_flush_pending_output
  md_flush_pending_output ();
#endif

  do
    {
      /* input_line_pointer->1st char of a flonum (we hope!).  */
      SKIP_WHITESPACE ();

      /* Skip any 0{letter} that may be present. Don't even check if the
	 letter is legal. Someone may invent a "z" format and this routine
	 has no use for such information. Lusers beware: you get
	 diagnostics if your input is ill-conditioned.  */
      if (input_line_pointer[0] == '0'
	  && ISALPHA (input_line_pointer[1]))
	input_line_pointer += 2;

      /* Accept :xxxx, where the x's are hex digits, for a floating
	 point with the exact digits specified.  */
      if (input_line_pointer[0] == ':')
	{
	  ++input_line_pointer;
	  length = hex_float (float_type, temp);
	  if (length < 0)
	    {
	      ignore_rest_of_line ();
	      return;
	    }
	}
      else
	{
	  err = md_atof (float_type, temp, &length);
	  know (length <= MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT);
	  know (length > 0);
	  if (err)
	    {
	      as_bad (_("bad floating literal: %s"), err);
	      ignore_rest_of_line ();
	      return;
	    }
	}

      if (!need_pass_2)
	{
	  int count;

	  count = 1;

#ifdef REPEAT_CONS_EXPRESSIONS
	  if (*input_line_pointer == ':')
	    {
	      expressionS count_exp;

	      ++input_line_pointer;
	      expression (&count_exp);

	      if (count_exp.X_op != O_constant
		  || count_exp.X_add_number <= 0)
		as_warn (_("unresolvable or nonpositive repeat count; using 1"));
	      else
		count = count_exp.X_add_number;
	    }
#endif

	  while (--count >= 0)
	    {
	      p = frag_more (length);
	      memcpy (p, temp, (unsigned int) length);
	    }
	}
      SKIP_WHITESPACE ();
    }
  while (*input_line_pointer++ == ',');

  /* Put terminator back into stream.  */
  --input_line_pointer;
  demand_empty_rest_of_line ();
}