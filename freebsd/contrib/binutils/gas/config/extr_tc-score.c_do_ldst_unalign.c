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
struct TYPE_2__ {unsigned int instruction; void* error; } ;

/* Variables and functions */
 void* BAD_ARGS ; 
 void* ERR_FOR_SCORE5U_ATOMIC ; 
 scalar_t__ FAIL ; 
 unsigned int LDST_UNALIGN_MASK ; 
 int /*<<< orphan*/  REG_TYPE_SCORE ; 
 unsigned int UA_LCE ; 
 unsigned int UA_LCW ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  as_warn (void*,void*) ; 
 int end_of_line (char*) ; 
 TYPE_1__ inst ; 
 int reg_required_here (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 
 int university_version ; 

__attribute__((used)) static void
do_ldst_unalign (char *str)
{
  int conflict_reg;

  if (university_version == 1)
    {
      inst.error = ERR_FOR_SCORE5U_ATOMIC;
      return;
    }

  skip_whitespace (str);

  /* lcb/scb [rA]+.  */
  if (*str == '[')
    {
      str++;
      skip_whitespace (str);

      if (reg_required_here (&str, 15, REG_TYPE_SCORE) == (int) FAIL)
	return;

      if (*str++ == ']')
        {
          if (*str++ != '+')
            {
              inst.error = _("missing +");
              return;
            }
        }
      else
        {
          inst.error = _("missing ]");
          return;
        }

      if (end_of_line (str) == (int) FAIL)
	return;
    }
  /* lcw/lce/scb/sce rD, [rA]+.  */
  else
    {
      if (((conflict_reg = reg_required_here (&str, 20, REG_TYPE_SCORE)) == (int) FAIL)
          || (skip_past_comma (&str) == (int) FAIL))
        {
          return;
        }

      skip_whitespace (str);
      if (*str++ == '[')
        {
          int reg;

          skip_whitespace (str);
          if ((reg = reg_required_here (&str, 15, REG_TYPE_SCORE)) == (int) FAIL)
            {
              return;
            }

          /* Conflicts can occur on stores as well as loads.  */
          conflict_reg = (conflict_reg == reg);
          skip_whitespace (str);
          if (*str++ == ']')
            {
              unsigned int ldst_func = inst.instruction & LDST_UNALIGN_MASK;

              if (*str++ == '+')
                {
                  if (conflict_reg)
                    {
                      as_warn (_("%s register same as write-back base"),
                               ((ldst_func & UA_LCE) || (ldst_func & UA_LCW)
                                ? _("destination") : _("source")));
                    }
                }
              else
                {
                  inst.error = _("missing +");
                  return;
                }

              if (end_of_line (str) == (int) FAIL)
		return;
            }
          else
            {
              inst.error = _("missing ]");
              return;
            }
        }
      else
        {
          inst.error = BAD_ARGS;
          return;
        }
    }
}