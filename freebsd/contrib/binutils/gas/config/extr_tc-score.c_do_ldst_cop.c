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
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ARGS ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  REG_TYPE_SCORE_CR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _IMM10_RSHIFT_2 ; 
 int /*<<< orphan*/  end_of_line (char*) ; 
 int exp_ldst_offset (char**,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static void
do_ldst_cop (char *str)
{
  skip_whitespace (str);

  if ((reg_required_here (&str, 15, REG_TYPE_SCORE_CR) == (int) FAIL)
      || (skip_past_comma (&str) == (int) FAIL))
    return;

  if (*str == '[')
    {
      str++;
      skip_whitespace (str);

      if (reg_required_here (&str, 20, REG_TYPE_SCORE) == (int) FAIL)
	return;

      skip_whitespace (str);

      if (*str++ != ']')
        {
          if (exp_ldst_offset (&str, 5, _IMM10_RSHIFT_2) == (int) FAIL)
	    return;

          skip_whitespace (str);
          if (*str++ != ']')
            {
              inst.error = _("missing ]");
              return;
            }
        }

      end_of_line (str);
    }
  else
    inst.error = BAD_ARGS;
}