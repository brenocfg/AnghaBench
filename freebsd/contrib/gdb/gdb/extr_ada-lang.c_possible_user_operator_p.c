#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct value {int dummy; } ;
struct type {int dummy; } ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;

/* Variables and functions */
#define  BINOP_ADD 148 
#define  BINOP_BITWISE_AND 147 
#define  BINOP_BITWISE_IOR 146 
#define  BINOP_BITWISE_XOR 145 
#define  BINOP_CONCAT 144 
#define  BINOP_DIV 143 
#define  BINOP_EQUAL 142 
#define  BINOP_EXP 141 
#define  BINOP_GEQ 140 
#define  BINOP_GTR 139 
#define  BINOP_LEQ 138 
#define  BINOP_LESS 137 
#define  BINOP_MOD 136 
#define  BINOP_MUL 135 
#define  BINOP_NOTEQUAL 134 
#define  BINOP_REM 133 
#define  BINOP_SUB 132 
 int /*<<< orphan*/  TYPE_CODE (struct type*) ; 
 int /*<<< orphan*/  TYPE_CODE_ARRAY ; 
 int /*<<< orphan*/  TYPE_CODE_PTR ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
#define  UNOP_ABS 131 
#define  UNOP_LOGICAL_NOT 130 
#define  UNOP_NEG 129 
#define  UNOP_PLUS 128 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_type_p (struct type*) ; 
 int /*<<< orphan*/  numeric_type_p (struct type*) ; 
 int /*<<< orphan*/  scalar_type_p (struct type*) ; 

__attribute__((used)) static int
possible_user_operator_p (enum exp_opcode op, struct value *args[])
{
  struct type *type0 = check_typedef (VALUE_TYPE (args[0]));
  struct type *type1 =
    (args[1] == NULL) ? NULL : check_typedef (VALUE_TYPE (args[1]));

  switch (op)
    {
    default:
      return 0;

    case BINOP_ADD:
    case BINOP_SUB:
    case BINOP_MUL:
    case BINOP_DIV:
      return (!(numeric_type_p (type0) && numeric_type_p (type1)));

    case BINOP_REM:
    case BINOP_MOD:
    case BINOP_BITWISE_AND:
    case BINOP_BITWISE_IOR:
    case BINOP_BITWISE_XOR:
      return (!(integer_type_p (type0) && integer_type_p (type1)));

    case BINOP_EQUAL:
    case BINOP_NOTEQUAL:
    case BINOP_LESS:
    case BINOP_GTR:
    case BINOP_LEQ:
    case BINOP_GEQ:
      return (!(scalar_type_p (type0) && scalar_type_p (type1)));

    case BINOP_CONCAT:
      return ((TYPE_CODE (type0) != TYPE_CODE_ARRAY &&
	       (TYPE_CODE (type0) != TYPE_CODE_PTR ||
		TYPE_CODE (TYPE_TARGET_TYPE (type0))
		!= TYPE_CODE_ARRAY))
	      || (TYPE_CODE (type1) != TYPE_CODE_ARRAY &&
		  (TYPE_CODE (type1) != TYPE_CODE_PTR ||
		   TYPE_CODE (TYPE_TARGET_TYPE (type1)) != TYPE_CODE_ARRAY)));

    case BINOP_EXP:
      return (!(numeric_type_p (type0) && integer_type_p (type1)));

    case UNOP_NEG:
    case UNOP_PLUS:
    case UNOP_LOGICAL_NOT:
    case UNOP_ABS:
      return (!numeric_type_p (type0));

    }
}