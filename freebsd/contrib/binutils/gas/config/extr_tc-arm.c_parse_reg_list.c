#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_2__ expressionS ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ pc_rel; int /*<<< orphan*/  exp; } ;
struct TYPE_8__ {TYPE_1__ reloc; void* error; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_ARM_MULTI ; 
 int FAIL ; 
 int /*<<< orphan*/  GE_NO_PREFIX ; 
 scalar_t__ O_constant ; 
 size_t REG_TYPE_RN ; 
 void* _ (char*) ; 
 int arm_reg_parse (char**,size_t) ; 
 int /*<<< orphan*/  as_tsktsk (void*,...) ; 
 int /*<<< orphan*/  first_error (void*) ; 
 TYPE_5__ inst ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ my_get_expression (TYPE_2__*,char**,int /*<<< orphan*/ ) ; 
 char** reg_expected_msgs ; 
 int skip_past_comma (char**) ; 

__attribute__((used)) static long
parse_reg_list (char ** strp)
{
  char * str = * strp;
  long	 range = 0;
  int	 another_range;

  /* We come back here if we get ranges concatenated by '+' or '|'.  */
  do
    {
      another_range = 0;

      if (*str == '{')
	{
	  int in_range = 0;
	  int cur_reg = -1;

	  str++;
	  do
	    {
	      int reg;

	      if ((reg = arm_reg_parse (&str, REG_TYPE_RN)) == FAIL)
		{
		  first_error (_(reg_expected_msgs[REG_TYPE_RN]));
		  return FAIL;
		}

	      if (in_range)
		{
		  int i;

		  if (reg <= cur_reg)
		    {
		      first_error (_("bad range in register list"));
		      return FAIL;
		    }

		  for (i = cur_reg + 1; i < reg; i++)
		    {
		      if (range & (1 << i))
			as_tsktsk
			  (_("Warning: duplicated register (r%d) in register list"),
			   i);
		      else
			range |= 1 << i;
		    }
		  in_range = 0;
		}

	      if (range & (1 << reg))
		as_tsktsk (_("Warning: duplicated register (r%d) in register list"),
			   reg);
	      else if (reg <= cur_reg)
		as_tsktsk (_("Warning: register range not in ascending order"));

	      range |= 1 << reg;
	      cur_reg = reg;
	    }
	  while (skip_past_comma (&str) != FAIL
		 || (in_range = 1, *str++ == '-'));
	  str--;

	  if (*str++ != '}')
	    {
	      first_error (_("missing `}'"));
	      return FAIL;
	    }
	}
      else
	{
	  expressionS expr;

	  if (my_get_expression (&expr, &str, GE_NO_PREFIX))
	    return FAIL;

	  if (expr.X_op == O_constant)
	    {
	      if (expr.X_add_number
		  != (expr.X_add_number & 0x0000ffff))
		{
		  inst.error = _("invalid register mask");
		  return FAIL;
		}

	      if ((range & expr.X_add_number) != 0)
		{
		  int regno = range & expr.X_add_number;

		  regno &= -regno;
		  regno = (1 << regno) - 1;
		  as_tsktsk
		    (_("Warning: duplicated register (r%d) in register list"),
		     regno);
		}

	      range |= expr.X_add_number;
	    }
	  else
	    {
	      if (inst.reloc.type != 0)
		{
		  inst.error = _("expression too complex");
		  return FAIL;
		}

	      memcpy (&inst.reloc.exp, &expr, sizeof (expressionS));
	      inst.reloc.type = BFD_RELOC_ARM_MULTI;
	      inst.reloc.pc_rel = 0;
	    }
	}

      if (*str == '|' || *str == '+')
	{
	  str++;
	  another_range = 1;
	}
    }
  while (another_range);

  *strp = str;
  return range;
}