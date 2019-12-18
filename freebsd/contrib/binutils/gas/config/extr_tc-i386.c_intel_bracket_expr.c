#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* start; } ;
struct TYPE_9__ {scalar_t__ index_reg; scalar_t__ base_reg; int /*<<< orphan*/ * types; TYPE_1__* op; } ;
struct TYPE_8__ {int op_modifier; char* op_string; char* disp; int is_mem; int /*<<< orphan*/  in_bracket; scalar_t__ in_offset; } ;
struct TYPE_7__ {int opcode_modifier; } ;
struct TYPE_6__ {scalar_t__ regs; } ;

/* Variables and functions */
 int Jump ; 
 int /*<<< orphan*/  JumpAbsolute ; 
 int JumpDword ; 
 char T_NIL ; 
 int T_OFFSET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,int,char const*,int,char const*) ; 
 TYPE_5__* current_templates ; 
 TYPE_4__ i ; 
 scalar_t__ intel_expr () ; 
 int intel_match_token (char) ; 
 TYPE_3__ intel_parser ; 
 int /*<<< orphan*/  quiet_warnings ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 size_t this_operand ; 

__attribute__((used)) static int
intel_bracket_expr (void)
{
  int was_offset = intel_parser.op_modifier & (1 << T_OFFSET);
  const char *start = intel_parser.op_string;
  int len;

  if (i.op[this_operand].regs)
    return intel_match_token (T_NIL);

  intel_match_token ('[');

  /* Mark as a memory operand only if it's not already known to be an
     offset expression.  If it's an offset expression, we need to keep
     the brace in.  */
  if (!intel_parser.in_offset)
    {
      ++intel_parser.in_bracket;

      /* Operands for jump/call inside brackets denote absolute addresses.  */
      if (current_templates->start->opcode_modifier & (Jump | JumpDword))
	i.types[this_operand] |= JumpAbsolute;

      /* Unfortunately gas always diverged from MASM in a respect that can't
	 be easily fixed without risking to break code sequences likely to be
	 encountered (the testsuite even check for this): MASM doesn't consider
	 an expression inside brackets unconditionally as a memory reference.
	 When that is e.g. a constant, an offset expression, or the sum of the
	 two, this is still taken as a constant load. gas, however, always
	 treated these as memory references. As a compromise, we'll try to make
	 offset expressions inside brackets work the MASM way (since that's
	 less likely to be found in real world code), but make constants alone
	 continue to work the traditional gas way. In either case, issue a
	 warning.  */
      intel_parser.op_modifier &= ~was_offset;
    }
  else
    strcat (intel_parser.disp, "[");

  /* Add a '+' to the displacement string if necessary.  */
  if (*intel_parser.disp != '\0'
      && *(intel_parser.disp + strlen (intel_parser.disp) - 1) != '+')
    strcat (intel_parser.disp, "+");

  if (intel_expr ()
      && (len = intel_parser.op_string - start - 1,
	  intel_match_token (']')))
    {
      /* Preserve brackets when the operand is an offset expression.  */
      if (intel_parser.in_offset)
	strcat (intel_parser.disp, "]");
      else
	{
	  --intel_parser.in_bracket;
	  if (i.base_reg || i.index_reg)
	    intel_parser.is_mem = 1;
	  if (!intel_parser.is_mem)
	    {
	      if (!(intel_parser.op_modifier & (1 << T_OFFSET)))
		/* Defer the warning until all of the operand was parsed.  */
		intel_parser.is_mem = -1;
	      else if (!quiet_warnings)
		as_warn (_("`[%.*s]' taken to mean just `%.*s'"),
			 len, start, len, start);
	    }
	}
      intel_parser.op_modifier |= was_offset;

      return 1;
    }
  return 0;
}