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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  ABS_EXPR 198 
#define  ADDR_EXPR 197 
#define  ARRAY_REF 196 
#define  BIT_AND_EXPR 195 
#define  BIT_IOR_EXPR 194 
#define  BIT_NOT_EXPR 193 
#define  BIT_XOR_EXPR 192 
#define  CALL_EXPR 191 
#define  COMPLEX_CST 190 
#define  COMPLEX_EXPR 189 
#define  COMPONENT_REF 188 
#define  COMPOUND_EXPR 187 
#define  COMPOUND_LITERAL_EXPR 186 
#define  COND_EXPR 185 
#define  CONJ_EXPR 184 
#define  CONSTRUCTOR 183 
#define  CONST_DECL 182 
#define  CONVERT_EXPR 181 
#define  EQ_EXPR 180 
#define  ERROR_MARK 179 
#define  FIELD_DECL 178 
#define  FIX_TRUNC_EXPR 177 
#define  FLOAT_EXPR 176 
#define  FUNCTION_DECL 175 
#define  GE_EXPR 174 
#define  GT_EXPR 173 
#define  IDENTIFIER_NODE 172 
#define  IMAGPART_EXPR 171 
#define  INDIRECT_REF 170 
#define  INIT_EXPR 169 
#define  INTEGER_CST 168 
#define  LABEL_DECL 167 
#define  LE_EXPR 166 
#define  LSHIFT_EXPR 165 
#define  LTGT_EXPR 164 
#define  LT_EXPR 163 
#define  MINUS_EXPR 162 
#define  MODIFY_EXPR 161 
#define  MULT_EXPR 160 
#define  NEGATE_EXPR 159 
#define  NE_EXPR 158 
#define  NON_LVALUE_EXPR 157 
#define  NOP_EXPR 156 
#define  ORDERED_EXPR 155 
#define  PARM_DECL 154 
#define  PLUS_EXPR 153 
#define  POSTDECREMENT_EXPR 152 
#define  POSTINCREMENT_EXPR 151 
#define  PREDECREMENT_EXPR 150 
#define  PREINCREMENT_EXPR 149 
#define  REALPART_EXPR 148 
#define  REAL_CST 147 
#define  RESULT_DECL 146 
#define  RSHIFT_EXPR 145 
#define  SAVE_EXPR 144 
#define  STRING_CST 143 
#define  TARGET_EXPR 142 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  TRUNC_DIV_EXPR 141 
#define  TRUNC_MOD_EXPR 140 
#define  TRUTH_ANDIF_EXPR 139 
#define  TRUTH_NOT_EXPR 138 
#define  TRUTH_ORIF_EXPR 137 
#define  UNEQ_EXPR 136 
#define  UNGE_EXPR 135 
#define  UNGT_EXPR 134 
#define  UNLE_EXPR 133 
#define  UNLT_EXPR 132 
#define  UNORDERED_EXPR 131 
#define  VAR_DECL 130 
#define  VA_ARG_EXPR 129 
#define  VECTOR_CST 128 
 int /*<<< orphan*/  pp_assignment_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_additive_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_and_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_cast_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_equality_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_exclusive_or_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_floating_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_inclusive_or_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_integer_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_logical_and_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_logical_or_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_relational_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_shift_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_string_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_unary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_conditional_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_multiplicative_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_postfix_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_primary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_expression (c_pretty_printer *pp, tree e)
{
  switch (TREE_CODE (e))
    {
    case INTEGER_CST:
      pp_c_integer_constant (pp, e);
      break;

    case REAL_CST:
      pp_c_floating_constant (pp, e);
      break;

    case STRING_CST:
      pp_c_string_literal (pp, e);
      break;

    case IDENTIFIER_NODE:
    case FUNCTION_DECL:
    case VAR_DECL:
    case CONST_DECL:
    case PARM_DECL:
    case RESULT_DECL:
    case FIELD_DECL:
    case LABEL_DECL:
    case ERROR_MARK:
      pp_primary_expression (pp, e);
      break;

    case POSTINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case ARRAY_REF:
    case CALL_EXPR:
    case COMPONENT_REF:
    case COMPLEX_CST:
    case COMPLEX_EXPR:
    case VECTOR_CST:
    case ORDERED_EXPR:
    case UNORDERED_EXPR:
    case LTGT_EXPR:
    case UNEQ_EXPR:
    case UNLE_EXPR:
    case UNLT_EXPR:
    case UNGE_EXPR:
    case UNGT_EXPR:
    case ABS_EXPR:
    case CONSTRUCTOR:
    case COMPOUND_LITERAL_EXPR:
    case VA_ARG_EXPR:
      pp_postfix_expression (pp, e);
      break;

    case CONJ_EXPR:
    case ADDR_EXPR:
    case INDIRECT_REF:
    case NEGATE_EXPR:
    case BIT_NOT_EXPR:
    case TRUTH_NOT_EXPR:
    case PREINCREMENT_EXPR:
    case PREDECREMENT_EXPR:
    case REALPART_EXPR:
    case IMAGPART_EXPR:
      pp_c_unary_expression (pp, e);
      break;

    case FLOAT_EXPR:
    case FIX_TRUNC_EXPR:
    case CONVERT_EXPR:
    case NOP_EXPR:
      pp_c_cast_expression (pp, e);
      break;

    case MULT_EXPR:
    case TRUNC_MOD_EXPR:
    case TRUNC_DIV_EXPR:
      pp_multiplicative_expression (pp, e);
      break;

    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
      pp_c_shift_expression (pp, e);
      break;

    case LT_EXPR:
    case GT_EXPR:
    case LE_EXPR:
    case GE_EXPR:
      pp_c_relational_expression (pp, e);
      break;

    case BIT_AND_EXPR:
      pp_c_and_expression (pp, e);
      break;

    case BIT_XOR_EXPR:
      pp_c_exclusive_or_expression (pp, e);
      break;

    case BIT_IOR_EXPR:
      pp_c_inclusive_or_expression (pp, e);
      break;

    case TRUTH_ANDIF_EXPR:
      pp_c_logical_and_expression (pp, e);
      break;

    case TRUTH_ORIF_EXPR:
      pp_c_logical_or_expression (pp, e);
      break;

    case EQ_EXPR:
    case NE_EXPR:
      pp_c_equality_expression (pp, e);
      break;

    case COND_EXPR:
      pp_conditional_expression (pp, e);
      break;

    case PLUS_EXPR:
    case MINUS_EXPR:
      pp_c_additive_expression (pp, e);
      break;

    case MODIFY_EXPR:
    case INIT_EXPR:
      pp_assignment_expression (pp, e);
      break;

    case COMPOUND_EXPR:
      pp_c_left_paren (pp);
      pp_expression (pp, TREE_OPERAND (e, 0));
      pp_separate_with (pp, ',');
      pp_assignment_expression (pp, TREE_OPERAND (e, 1));
      pp_c_right_paren (pp);
      break;

    case NON_LVALUE_EXPR:
    case SAVE_EXPR:
      pp_expression (pp, TREE_OPERAND (e, 0));
      break;

    case TARGET_EXPR:
      pp_postfix_expression (pp, TREE_OPERAND (e, 1));
      break;

    default:
      pp_unsupported_tree (pp, e);
      break;
    }
}