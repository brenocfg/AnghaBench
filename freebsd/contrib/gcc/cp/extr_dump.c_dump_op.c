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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  dump_info_p ;

/* Variables and functions */
#define  ADDR_EXPR 165 
#define  ARRAY_REF 164 
#define  BIT_AND_EXPR 163 
#define  BIT_IOR_EXPR 162 
#define  BIT_NOT_EXPR 161 
#define  BIT_XOR_EXPR 160 
#define  CALL_EXPR 159 
#define  COMPONENT_REF 158 
#define  COMPOUND_EXPR 157 
 int /*<<< orphan*/  DECL_ASSIGNMENT_OPERATOR_P (int /*<<< orphan*/ ) ; 
 int DECL_OVERLOADED_OPERATOR_P (int /*<<< orphan*/ ) ; 
#define  DELETE_EXPR 156 
#define  EQ_EXPR 155 
#define  GE_EXPR 154 
#define  GT_EXPR 153 
#define  INDIRECT_REF 152 
#define  LE_EXPR 151 
#define  LSHIFT_EXPR 150 
#define  LT_EXPR 149 
#define  MEMBER_REF 148 
#define  MINUS_EXPR 147 
#define  MULT_EXPR 146 
#define  NEGATE_EXPR 145 
#define  NEW_EXPR 144 
#define  NE_EXPR 143 
#define  NOP_EXPR 142 
#define  PLUS_EXPR 141 
#define  POSTDECREMENT_EXPR 140 
#define  POSTINCREMENT_EXPR 139 
#define  PREDECREMENT_EXPR 138 
#define  PREINCREMENT_EXPR 137 
#define  RSHIFT_EXPR 136 
#define  TRUNC_DIV_EXPR 135 
#define  TRUNC_MOD_EXPR 134 
#define  TRUTH_ANDIF_EXPR 133 
#define  TRUTH_NOT_EXPR 132 
#define  TRUTH_ORIF_EXPR 131 
#define  UNARY_PLUS_EXPR 130 
#define  VEC_DELETE_EXPR 129 
#define  VEC_NEW_EXPR 128 
 int /*<<< orphan*/  dump_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dump_op (dump_info_p di, tree t)
{
  switch (DECL_OVERLOADED_OPERATOR_P (t)) {
    case NEW_EXPR:
      dump_string (di, "new");
      break;
    case VEC_NEW_EXPR:
      dump_string (di, "vecnew");
      break;
    case DELETE_EXPR:
      dump_string (di, "delete");
      break;
    case VEC_DELETE_EXPR:
      dump_string (di, "vecdelete");
      break;
    case UNARY_PLUS_EXPR:
      dump_string (di, "pos");
      break;
    case NEGATE_EXPR:
      dump_string (di, "neg");
      break;
    case ADDR_EXPR:
      dump_string (di, "addr");
      break;
    case INDIRECT_REF:
      dump_string(di, "deref");
      break;
    case BIT_NOT_EXPR:
      dump_string(di, "not");
      break;
    case TRUTH_NOT_EXPR:
      dump_string(di, "lnot");
      break;
    case PREINCREMENT_EXPR:
      dump_string(di, "preinc");
      break;
    case PREDECREMENT_EXPR:
      dump_string(di, "predec");
      break;
    case PLUS_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "plusassign");
      else
	dump_string(di, "plus");
      break;
    case MINUS_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "minusassign");
      else
	dump_string(di, "minus");
      break;
    case MULT_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "multassign");
      else
	dump_string (di, "mult");
      break;
    case TRUNC_DIV_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "divassign");
      else
	dump_string (di, "div");
      break;
    case TRUNC_MOD_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	 dump_string (di, "modassign");
      else
	dump_string (di, "mod");
      break;
    case BIT_AND_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "andassign");
      else
	dump_string (di, "and");
      break;
    case BIT_IOR_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "orassign");
      else
	dump_string (di, "or");
      break;
    case BIT_XOR_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "xorassign");
      else
	dump_string (di, "xor");
      break;
    case LSHIFT_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "lshiftassign");
      else
	dump_string (di, "lshift");
      break;
    case RSHIFT_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "rshiftassign");
      else
	dump_string (di, "rshift");
      break;
    case EQ_EXPR:
      dump_string (di, "eq");
      break;
    case NE_EXPR:
      dump_string (di, "ne");
      break;
    case LT_EXPR:
      dump_string (di, "lt");
      break;
    case GT_EXPR:
      dump_string (di, "gt");
      break;
    case LE_EXPR:
      dump_string (di, "le");
      break;
    case GE_EXPR:
      dump_string (di, "ge");
      break;
    case TRUTH_ANDIF_EXPR:
      dump_string (di, "land");
      break;
    case TRUTH_ORIF_EXPR:
      dump_string (di, "lor");
      break;
    case COMPOUND_EXPR:
      dump_string (di, "compound");
      break;
    case MEMBER_REF:
      dump_string (di, "memref");
      break;
    case COMPONENT_REF:
      dump_string (di, "ref");
      break;
    case ARRAY_REF:
      dump_string (di, "subs");
      break;
    case POSTINCREMENT_EXPR:
      dump_string (di, "postinc");
      break;
    case POSTDECREMENT_EXPR:
      dump_string (di, "postdec");
      break;
    case CALL_EXPR:
      dump_string (di, "call");
      break;
    case NOP_EXPR:
      if (DECL_ASSIGNMENT_OPERATOR_P (t))
	dump_string (di, "assign");
      break;
    default:
      break;
  }
}