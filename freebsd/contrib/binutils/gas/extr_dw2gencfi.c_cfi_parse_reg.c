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
struct TYPE_3__ {int X_op; int X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
#define  O_constant 129 
#define  O_register 128 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expression_and_evaluate (TYPE_1__*) ; 
 char get_symbol_end () ; 
 char* input_line_pointer ; 
 scalar_t__ is_name_beginner (char) ; 
 int tc_regname_to_dw2regnum (char*) ; 

__attribute__((used)) static unsigned
cfi_parse_reg (void)
{
  int regno;
  expressionS exp;

#ifdef tc_regname_to_dw2regnum
  SKIP_WHITESPACE ();
  if (is_name_beginner (*input_line_pointer)
      || (*input_line_pointer == '%'
	  && is_name_beginner (*++input_line_pointer)))
    {
      char *name, c;

      name = input_line_pointer;
      c = get_symbol_end ();

      if ((regno = tc_regname_to_dw2regnum (name)) < 0)
	{
	  as_bad (_("bad register expression"));
	  regno = 0;
	}

      *input_line_pointer = c;
      return regno;
    }
#endif

  expression_and_evaluate (&exp);
  switch (exp.X_op)
    {
    case O_register:
    case O_constant:
      regno = exp.X_add_number;
      break;

    default:
      as_bad (_("bad register expression"));
      regno = 0;
      break;
    }

  return regno;
}