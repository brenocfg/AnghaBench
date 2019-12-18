#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ segT ;
struct TYPE_6__ {scalar_t__ X_op; scalar_t__ X_op_symbol; scalar_t__ X_add_symbol; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_7__ {int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 int FAIL ; 
#define  GE_IMM_PREFIX 131 
#define  GE_NO_PREFIX 130 
#define  GE_OPT_PREFIX 129 
#define  GE_OPT_PREFIX_BIG 128 
 scalar_t__ O_big ; 
 scalar_t__ O_illegal ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ absolute_section ; 
 scalar_t__ bss_section ; 
 scalar_t__ data_section ; 
 scalar_t__ expression (TYPE_1__*) ; 
 int in_my_get_expression ; 
 char* input_line_pointer ; 
 TYPE_4__ inst ; 
 int /*<<< orphan*/  is_immediate_prefix (char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ text_section ; 
 scalar_t__ undefined_section ; 
 scalar_t__ unified_syntax ; 
 scalar_t__ walk_no_bignums (scalar_t__) ; 

__attribute__((used)) static int
my_get_expression (expressionS * ep, char ** str, int prefix_mode)
{
  char * save_in;
  segT	 seg;

  /* In unified syntax, all prefixes are optional.  */
  if (unified_syntax)
    prefix_mode = (prefix_mode == GE_OPT_PREFIX_BIG) ? prefix_mode
                  : GE_OPT_PREFIX;

  switch (prefix_mode)
    {
    case GE_NO_PREFIX: break;
    case GE_IMM_PREFIX:
      if (!is_immediate_prefix (**str))
	{
	  inst.error = _("immediate expression requires a # prefix");
	  return FAIL;
	}
      (*str)++;
      break;
    case GE_OPT_PREFIX:
    case GE_OPT_PREFIX_BIG:
      if (is_immediate_prefix (**str))
	(*str)++;
      break;
    default: abort ();
    }

  memset (ep, 0, sizeof (expressionS));

  save_in = input_line_pointer;
  input_line_pointer = *str;
  in_my_get_expression = 1;
  seg = expression (ep);
  in_my_get_expression = 0;

  if (ep->X_op == O_illegal)
    {
      /* We found a bad expression in md_operand().  */
      *str = input_line_pointer;
      input_line_pointer = save_in;
      if (inst.error == NULL)
	inst.error = _("bad expression");
      return 1;
    }

#ifdef OBJ_AOUT
  if (seg != absolute_section
      && seg != text_section
      && seg != data_section
      && seg != bss_section
      && seg != undefined_section)
    {
      inst.error = _("bad segment");
      *str = input_line_pointer;
      input_line_pointer = save_in;
      return 1;
    }
#endif

  /* Get rid of any bignums now, so that we don't generate an error for which
     we can't establish a line number later on.	 Big numbers are never valid
     in instructions, which is where this routine is always called.  */
  if (prefix_mode != GE_OPT_PREFIX_BIG
      && (ep->X_op == O_big
          || (ep->X_add_symbol
	      && (walk_no_bignums (ep->X_add_symbol)
	          || (ep->X_op_symbol
		      && walk_no_bignums (ep->X_op_symbol))))))
    {
      inst.error = _("invalid constant");
      *str = input_line_pointer;
      input_line_pointer = save_in;
      return 1;
    }

  *str = input_line_pointer;
  input_line_pointer = save_in;
  return 0;
}