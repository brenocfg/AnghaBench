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
struct TYPE_3__ {int X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISALPHA (char) ; 
 int /*<<< orphan*/  O_register ; 
 int /*<<< orphan*/  REG_NAME_CNT ; 
 int /*<<< orphan*/  TRUE ; 
 char get_symbol_end () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  pre_defined_registers ; 
 int reg_name_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reg_names_p ; 

__attribute__((used)) static bfd_boolean
register_name (expressionS *expressionP)
{
  int reg_number;
  char *name;
  char *start;
  char c;

  /* Find the spelling of the operand.  */
  start = name = input_line_pointer;
  if (name[0] == '%' && ISALPHA (name[1]))
    name = ++input_line_pointer;

  else if (!reg_names_p || !ISALPHA (name[0]))
    return FALSE;

  c = get_symbol_end ();
  reg_number = reg_name_search (pre_defined_registers, REG_NAME_CNT, name);

  /* Put back the delimiting char.  */
  *input_line_pointer = c;

  /* Look to see if it's in the register table.  */
  if (reg_number >= 0)
    {
      expressionP->X_op = O_register;
      expressionP->X_add_number = reg_number;

      /* Make the rest nice.  */
      expressionP->X_add_symbol = NULL;
      expressionP->X_op_symbol = NULL;
      return TRUE;
    }

  /* Reset the line as if we had not done anything.  */
  input_line_pointer = start;
  return FALSE;
}