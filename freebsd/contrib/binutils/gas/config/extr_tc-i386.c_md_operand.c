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
typedef  int /*<<< orphan*/  reg_entry ;
struct TYPE_3__ {int /*<<< orphan*/  const* X_add_number; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  O_register ; 
 scalar_t__ REGISTER_PREFIX ; 
 int i386_regtab ; 
 scalar_t__* input_line_pointer ; 
 int /*<<< orphan*/ * parse_real_register (scalar_t__*,char**) ; 

void
md_operand (expressionS *e)
{
  if (*input_line_pointer == REGISTER_PREFIX)
    {
      char *end;
      const reg_entry *r = parse_real_register (input_line_pointer, &end);

      if (r)
	{
	  e->X_op = O_register;
	  e->X_add_number = r - i386_regtab;
	  input_line_pointer = end;
	}
    }
}