#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; } ;
struct arc_ext_operand_value {struct arc_ext_operand_value* next; TYPE_1__ operand; } ;
typedef  void* offsetT ;
struct TYPE_8__ {void* X_add_number; void* X_op; } ;
typedef  TYPE_2__ expressionS ;
struct TYPE_9__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISALNUM (char) ; 
 void* O_register ; 
 int /*<<< orphan*/  arc_code_symbol (TYPE_2__*) ; 
 struct arc_ext_operand_value* arc_ext_operands ; 
 TYPE_5__* arc_reg_names ; 
 int arc_reg_names_count ; 
 int /*<<< orphan*/  as_bad (char*) ; 
 int /*<<< orphan*/  expression (TYPE_2__*) ; 
 char* input_line_pointer ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
md_operand (expressionS *expressionP)
{
  char *p = input_line_pointer;

  if (*p != '%')
    return;

  if (strncmp (p, "%st(", 4) == 0)
    {
      input_line_pointer += 4;
      expression (expressionP);
      if (*input_line_pointer != ')')
	{
	  as_bad ("missing ')' in %%-op");
	  return;
	}
      ++input_line_pointer;
      arc_code_symbol (expressionP);
    }
  else
    {
      /* It could be a register.  */
      int i, l;
      struct arc_ext_operand_value *ext_oper = arc_ext_operands;
      p++;

      while (ext_oper)
	{
	  l = strlen (ext_oper->operand.name);
	  if (!strncmp (p, ext_oper->operand.name, l) && !ISALNUM (*(p + l)))
	    {
	      input_line_pointer += l + 1;
	      expressionP->X_op = O_register;
	      expressionP->X_add_number = (offsetT) &ext_oper->operand;
	      return;
	    }
	  ext_oper = ext_oper->next;
	}
      for (i = 0; i < arc_reg_names_count; i++)
	{
	  l = strlen (arc_reg_names[i].name);
	  if (!strncmp (p, arc_reg_names[i].name, l) && !ISALNUM (*(p + l)))
	    {
	      input_line_pointer += l + 1;
	      expressionP->X_op = O_register;
	      expressionP->X_add_number = (offsetT) &arc_reg_names[i];
	      break;
	    }
	}
    }
}