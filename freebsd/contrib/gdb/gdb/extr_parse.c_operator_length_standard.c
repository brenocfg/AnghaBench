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
struct expression {TYPE_1__* elts; } ;
struct TYPE_2__ {int /*<<< orphan*/  longconst; scalar_t__ opcode; } ;

/* Variables and functions */
#define  BINOP_ASSIGN_MODIFY 171 
 scalar_t__ BINOP_END ; 
#define  BINOP_VAL 170 
 int /*<<< orphan*/  BYTES_TO_EXP_ELEM (int) ; 
 int HOST_CHAR_BIT ; 
#define  MULTI_SUBSCRIPT 169 
#define  OP_ARRAY 168 
#define  OP_BITSTRING 167 
#define  OP_BOOL 166 
#define  OP_COMPLEX 165 
#define  OP_DOUBLE 164 
#define  OP_EXPRSTRING 163 
#define  OP_F77_UNDETERMINED_ARGLIST 162 
#define  OP_FUNCALL 161 
#define  OP_INTERNALVAR 160 
#define  OP_LABELED 159 
#define  OP_LAST 158 
#define  OP_LONG 157 
#define  OP_M2_STRING 156 
#define  OP_NAME 155 
#define  OP_OBJC_MSGCALL 154 
#define  OP_OBJC_NSSTRING 153 
#define  OP_OBJC_SELECTOR 152 
#define  OP_OBJC_SELF 151 
#define  OP_REGISTER 150 
#define  OP_SCOPE 149 
#define  OP_STRING 148 
#define  OP_THIS 147 
#define  OP_TYPE 146 
#define  OP_VAR_VALUE 145 
#define  STRUCTOP_PTR 144 
#define  STRUCTOP_STRUCT 143 
#define  TERNOP_COND 142 
#define  TERNOP_SLICE 141 
#define  TERNOP_SLICE_COUNT 140 
#define  UNOP_ABS 139 
#define  UNOP_CAP 138 
#define  UNOP_CAST 137 
#define  UNOP_CHR 136 
#define  UNOP_FLOAT 135 
#define  UNOP_HIGH 134 
#define  UNOP_MAX 133 
#define  UNOP_MEMVAL 132 
#define  UNOP_MIN 131 
#define  UNOP_ODD 130 
#define  UNOP_ORD 129 
#define  UNOP_TRUNC 128 
 int /*<<< orphan*/  error (char*) ; 
 int longest_to_int (int /*<<< orphan*/ ) ; 

void
operator_length_standard (struct expression *expr, int endpos,
			  int *oplenp, int *argsp)
{
  int oplen = 1;
  int args = 0;
  int i;

  if (endpos < 1)
    error ("?error in operator_length_standard");

  i = (int) expr->elts[endpos - 1].opcode;

  switch (i)
    {
      /* C++  */
    case OP_SCOPE:
      oplen = longest_to_int (expr->elts[endpos - 2].longconst);
      oplen = 5 + BYTES_TO_EXP_ELEM (oplen + 1);
      break;

    case OP_LONG:
    case OP_DOUBLE:
    case OP_VAR_VALUE:
      oplen = 4;
      break;

    case OP_TYPE:
    case OP_BOOL:
    case OP_LAST:
    case OP_REGISTER:
    case OP_INTERNALVAR:
      oplen = 3;
      break;

    case OP_COMPLEX:
      oplen = 1;
      args = 2;
      break;

    case OP_FUNCALL:
    case OP_F77_UNDETERMINED_ARGLIST:
      oplen = 3;
      args = 1 + longest_to_int (expr->elts[endpos - 2].longconst);
      break;

    case OP_OBJC_MSGCALL:	/* Objective C message (method) call */
      oplen = 4;
      args = 1 + longest_to_int (expr->elts[endpos - 2].longconst);
      break;

    case UNOP_MAX:
    case UNOP_MIN:
      oplen = 3;
      break;

    case BINOP_VAL:
    case UNOP_CAST:
    case UNOP_MEMVAL:
      oplen = 3;
      args = 1;
      break;

    case UNOP_ABS:
    case UNOP_CAP:
    case UNOP_CHR:
    case UNOP_FLOAT:
    case UNOP_HIGH:
    case UNOP_ODD:
    case UNOP_ORD:
    case UNOP_TRUNC:
      oplen = 1;
      args = 1;
      break;

    case OP_LABELED:
    case STRUCTOP_STRUCT:
    case STRUCTOP_PTR:
      args = 1;
      /* fall through */
    case OP_M2_STRING:
    case OP_STRING:
    case OP_OBJC_NSSTRING:	/* Objective C Foundation Class NSString constant */
    case OP_OBJC_SELECTOR:	/* Objective C "@selector" pseudo-op */
    case OP_NAME:
    case OP_EXPRSTRING:
      oplen = longest_to_int (expr->elts[endpos - 2].longconst);
      oplen = 4 + BYTES_TO_EXP_ELEM (oplen + 1);
      break;

    case OP_BITSTRING:
      oplen = longest_to_int (expr->elts[endpos - 2].longconst);
      oplen = (oplen + HOST_CHAR_BIT - 1) / HOST_CHAR_BIT;
      oplen = 4 + BYTES_TO_EXP_ELEM (oplen);
      break;

    case OP_ARRAY:
      oplen = 4;
      args = longest_to_int (expr->elts[endpos - 2].longconst);
      args -= longest_to_int (expr->elts[endpos - 3].longconst);
      args += 1;
      break;

    case TERNOP_COND:
    case TERNOP_SLICE:
    case TERNOP_SLICE_COUNT:
      args = 3;
      break;

      /* Modula-2 */
    case MULTI_SUBSCRIPT:
      oplen = 3;
      args = 1 + longest_to_int (expr->elts[endpos - 2].longconst);
      break;

    case BINOP_ASSIGN_MODIFY:
      oplen = 3;
      args = 2;
      break;

      /* C++ */
    case OP_THIS:
    case OP_OBJC_SELF:
      oplen = 2;
      break;

    default:
      args = 1 + (i < (int) BINOP_END);
    }

  *oplenp = oplen;
  *argsp = args;
}