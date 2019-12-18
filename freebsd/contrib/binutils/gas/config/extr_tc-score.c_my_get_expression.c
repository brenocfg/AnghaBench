#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  segT ;
struct TYPE_5__ {scalar_t__ X_op; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/ * X_op_symbol; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_6__ {scalar_t__ type; void* error; } ;

/* Variables and functions */
 void* BAD_ARGS ; 
 scalar_t__ FAIL ; 
 scalar_t__ Insn_Type_SYN ; 
 scalar_t__ Insn_internal ; 
 scalar_t__ O_big ; 
 scalar_t__ O_illegal ; 
 scalar_t__ PC_DISP11div2 ; 
 scalar_t__ PC_DISP19div2 ; 
 scalar_t__ PC_DISP24div2 ; 
 scalar_t__ PC_DISP8div2 ; 
 scalar_t__ Rd_lvalueRs_SI15 ; 
 scalar_t__ Rd_rvalueRs_SI15 ; 
 int SUCCESS ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  expression (TYPE_1__*) ; 
 int in_my_get_expression ; 
 char* input_line_pointer ; 
 TYPE_3__ inst ; 
 scalar_t__ walk_no_bignums (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
my_get_expression (expressionS * ep, char **str)
{
  char *save_in;
  segT seg;

  save_in = input_line_pointer;
  input_line_pointer = *str;
  in_my_get_expression = 1;
  seg = expression (ep);
  in_my_get_expression = 0;

  if (ep->X_op == O_illegal)
    {
      *str = input_line_pointer;
      input_line_pointer = save_in;
      inst.error = _("illegal expression");
      return (int) FAIL;
    }
  /* Get rid of any bignums now, so that we don't generate an error for which
     we can't establish a line number later on.  Big numbers are never valid
     in instructions, which is where this routine is always called.  */
  if (ep->X_op == O_big
      || (ep->X_add_symbol
          && (walk_no_bignums (ep->X_add_symbol)
              || (ep->X_op_symbol && walk_no_bignums (ep->X_op_symbol)))))
    {
      inst.error = _("invalid constant");
      *str = input_line_pointer;
      input_line_pointer = save_in;
      return (int) FAIL;
    }

  if ((ep->X_add_symbol != NULL)
      && (inst.type != PC_DISP19div2)
      && (inst.type != PC_DISP8div2)
      && (inst.type != PC_DISP24div2)
      && (inst.type != PC_DISP11div2)
      && (inst.type != Insn_Type_SYN)
      && (inst.type != Rd_rvalueRs_SI15)
      && (inst.type != Rd_lvalueRs_SI15)
      && (inst.type != Insn_internal))
    {
      inst.error = BAD_ARGS;
      *str = input_line_pointer;
      input_line_pointer = save_in;
      return (int) FAIL;
    }

  *str = input_line_pointer;
  input_line_pointer = save_in;
  return SUCCESS;
}