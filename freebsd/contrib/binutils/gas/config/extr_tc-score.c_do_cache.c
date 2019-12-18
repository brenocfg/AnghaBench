#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int instruction; void* error; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* BAD_ARGS ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  SET_INSN_ERROR (int /*<<< orphan*/ *) ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  _IMM5 ; 
 int /*<<< orphan*/  _SIMM15 ; 
 int data_op2 (char**,int,int /*<<< orphan*/ ) ; 
 int end_of_line (char*) ; 
 int exp_ldst_offset (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
do_cache (char *str)
{
  skip_whitespace (str);

  if ((data_op2 (&str, 20, _IMM5) == (int) FAIL) || (skip_past_comma (&str) == (int) FAIL))
    {
      return;
    }
  else
    {
      int cache_op;

      cache_op = (inst.instruction >> 20) & 0x1F;
      sprintf (inst.name, "cache %d", cache_op);
    }

  if (*str == '[')
    {
      str++;
      skip_whitespace (str);

      if (reg_required_here (&str, 15, REG_TYPE_SCORE) == (int) FAIL)
	return;

      skip_whitespace (str);

      /* cache op, [rA]  */
      if (skip_past_comma (&str) == (int) FAIL)
        {
          SET_INSN_ERROR (NULL);
          if (*str != ']')
            {
              inst.error = _("missing ]");
              return;
            }
          str++;
        }
      /* cache op, [rA, simm15]  */
      else
        {
          if (exp_ldst_offset (&str, 0, _SIMM15) == (int) FAIL)
            {
              return;
            }

          skip_whitespace (str);
          if (*str++ != ']')
            {
              inst.error = _("missing ]");
              return;
            }
        }

      if (end_of_line (str) == (int) FAIL)
	return;
    }
  else
    {
      inst.error = BAD_ARGS;
    }
}