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
 int /*<<< orphan*/  ERR_FOR_SCORE5U_ATOMIC ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  end_of_line (char*) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int university_version ; 

__attribute__((used)) static void
do_ldst_atomic (char *str)
{
  if (university_version == 1)
    {
      inst.error = ERR_FOR_SCORE5U_ATOMIC;
      return;
    }

  skip_whitespace (str);

  if ((reg_required_here (&str, 20, REG_TYPE_SCORE) == (int) FAIL)
      || (skip_past_comma (&str) == (int) FAIL))
    {
      return;
    }
  else
    {

      skip_whitespace (str);
      if (*str++ == '[')
        {
          int reg;

          skip_whitespace (str);
          if ((reg = reg_required_here (&str, 15, REG_TYPE_SCORE)) == (int) FAIL)
            {
              return;
            }

          skip_whitespace (str);
          if (*str++ != ']')
            {
              inst.error = _("missing ]");
              return;
            }

          end_of_line (str);
        }
      else
	inst.error = BAD_ARGS;
    }
}