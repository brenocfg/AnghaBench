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
struct TYPE_3__ {int X_op; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
#define  O_absent 135 
#define  O_big 134 
#define  O_bit_not 133 
#define  O_constant 132 
#define  O_illegal 131 
#define  O_register 130 
#define  O_symbol 129 
#define  O_uminus 128 

__attribute__((used)) static void
clean_up_expression (expressionS *expressionP)
{
  switch (expressionP->X_op)
    {
    case O_illegal:
    case O_absent:
      expressionP->X_add_number = 0;
      /* Fall through.  */
    case O_big:
    case O_constant:
    case O_register:
      expressionP->X_add_symbol = NULL;
      /* Fall through.  */
    case O_symbol:
    case O_uminus:
    case O_bit_not:
      expressionP->X_op_symbol = NULL;
      break;
    default:
      break;
    }
}