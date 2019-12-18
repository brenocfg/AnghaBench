#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ X_op; unsigned long X_add_number; int X_unsigned; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int BITS_PER_CHAR ; 
 scalar_t__ O_absent ; 
 scalar_t__ O_constant ; 
 int TC_ADDRESS_BYTES () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,...) ; 
 int code_label ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 char* input_line_pointer ; 
 scalar_t__ is_it_end_of_statement () ; 
 int /*<<< orphan*/  md_cons_align (int) ; 
 int /*<<< orphan*/  md_flush_pending_output () ; 

__attribute__((used)) static void
l_cons (int nbytes)
{
  int c;
  expressionS exp;

#ifdef md_flush_pending_output
    md_flush_pending_output ();
#endif

  if (is_it_end_of_statement ())
    {
      demand_empty_rest_of_line ();
      return;
    }

#ifdef TC_ADDRESS_BYTES
  if (nbytes == 0)
    nbytes = TC_ADDRESS_BYTES ();
#endif

#ifdef md_cons_align
  md_cons_align (nbytes);
#endif

  c = 0;
  do
    {
      unsigned int bits_available = BITS_PER_CHAR * nbytes;
      char *hold = input_line_pointer;

      expression (&exp);

      if (*input_line_pointer == ':')
	{
	  /* Bitfields.  */
	  long value = 0;

	  for (;;)
	    {
	      unsigned long width;

	      if (*input_line_pointer != ':')
		{
		  input_line_pointer = hold;
		  break;
		}
	      if (exp.X_op == O_absent)
		{
		  as_warn (_("using a bit field width of zero"));
		  exp.X_add_number = 0;
		  exp.X_op = O_constant;
		}

	      if (exp.X_op != O_constant)
		{
		  *input_line_pointer = '\0';
		  as_bad (_("field width \"%s\" too complex for a bitfield"), hold);
		  *input_line_pointer = ':';
		  demand_empty_rest_of_line ();
		  return;
		}

	      if ((width = exp.X_add_number) >
		  (unsigned int)(BITS_PER_CHAR * nbytes))
		{
		  as_warn (_("field width %lu too big to fit in %d bytes: truncated to %d bits"), width, nbytes, (BITS_PER_CHAR * nbytes));
		  width = BITS_PER_CHAR * nbytes;
		}                   /* Too big.  */


	      if (width > bits_available)
		{
		  /* FIXME-SOMEDAY: backing up and reparsing is wasteful.  */
		  input_line_pointer = hold;
		  exp.X_add_number = value;
		  break;
		}

	      /* Skip ':'.  */
	      hold = ++input_line_pointer;

	      expression (&exp);
	      if (exp.X_op != O_constant)
		{
		  char cache = *input_line_pointer;

		  *input_line_pointer = '\0';
		  as_bad (_("field value \"%s\" too complex for a bitfield"), hold);
		  *input_line_pointer = cache;
		  demand_empty_rest_of_line ();
		  return;
		}

	      value |= ((~(-1 << width) & exp.X_add_number)
			<< ((BITS_PER_CHAR * nbytes) - bits_available));

	      if ((bits_available -= width) == 0
		  || is_it_end_of_statement ()
		  || *input_line_pointer != ',')
		break;

	      hold = ++input_line_pointer;
	      expression (&exp);
	    }

	  exp.X_add_number = value;
	  exp.X_op = O_constant;
	  exp.X_unsigned = 1;
	}

      if ((*(input_line_pointer) == '@') && (*(input_line_pointer +1) == 'c'))
	code_label = 1;
      emit_expr (&exp, (unsigned int) nbytes);
      ++c;
      if ((*(input_line_pointer) == '@') && (*(input_line_pointer +1) == 'c'))
	{
	  input_line_pointer +=3;
	  break;
	}
    }
  while ((*input_line_pointer++ == ','));

  /* Put terminator back into stream.  */
  input_line_pointer--;

  demand_empty_rest_of_line ();
}