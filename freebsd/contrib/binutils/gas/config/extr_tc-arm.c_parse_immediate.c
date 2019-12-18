#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_1__ expressionS ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_5__ {void* error; } ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  GE_IMM_PREFIX ; 
 int /*<<< orphan*/  GE_OPT_PREFIX ; 
 scalar_t__ O_constant ; 
 int SUCCESS ; 
 void* _ (char*) ; 
 TYPE_3__ inst ; 
 int /*<<< orphan*/  my_get_expression (TYPE_1__*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_immediate (char **str, int *val, int min, int max,
		 bfd_boolean prefix_opt)
{
  expressionS exp;
  my_get_expression (&exp, str, prefix_opt ? GE_OPT_PREFIX : GE_IMM_PREFIX);
  if (exp.X_op != O_constant)
    {
      inst.error = _("constant expression required");
      return FAIL;
    }

  if (exp.X_add_number < min || exp.X_add_number > max)
    {
      inst.error = _("immediate value out of range");
      return FAIL;
    }

  *val = exp.X_add_number;
  return SUCCESS;
}