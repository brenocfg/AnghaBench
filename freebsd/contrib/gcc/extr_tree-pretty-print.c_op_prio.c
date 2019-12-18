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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
#define  ABS_EXPR 210 
#define  ADDR_EXPR 209 
#define  ALIGN_INDIRECT_REF 208 
#define  ARRAY_RANGE_REF 207 
#define  ARRAY_REF 206 
#define  BIND_EXPR 205 
#define  BIT_AND_EXPR 204 
#define  BIT_IOR_EXPR 203 
#define  BIT_NOT_EXPR 202 
#define  BIT_XOR_EXPR 201 
#define  CALL_EXPR 200 
#define  CEIL_DIV_EXPR 199 
#define  CEIL_MOD_EXPR 198 
#define  COMPONENT_REF 197 
#define  COMPOUND_EXPR 196 
#define  COND_EXPR 195 
#define  CONVERT_EXPR 194 
#define  DOT_PROD_EXPR 193 
#define  EQ_EXPR 192 
#define  EXACT_DIV_EXPR 191 
#define  FIX_CEIL_EXPR 190 
#define  FIX_FLOOR_EXPR 189 
#define  FIX_ROUND_EXPR 188 
#define  FIX_TRUNC_EXPR 187 
#define  FLOAT_EXPR 186 
#define  FLOOR_DIV_EXPR 185 
#define  FLOOR_MOD_EXPR 184 
#define  GE_EXPR 183 
#define  GT_EXPR 182 
#define  IMAGPART_EXPR 181 
#define  INDIRECT_REF 180 
#define  INIT_EXPR 179 
#define  LE_EXPR 178 
#define  LROTATE_EXPR 177 
#define  LSHIFT_EXPR 176 
#define  LTGT_EXPR 175 
#define  LT_EXPR 174 
#define  MAX_EXPR 173 
#define  MINUS_EXPR 172 
#define  MIN_EXPR 171 
#define  MISALIGNED_INDIRECT_REF 170 
#define  MODIFY_EXPR 169 
#define  MULT_EXPR 168 
#define  NEGATE_EXPR 167 
#define  NE_EXPR 166 
#define  NON_LVALUE_EXPR 165 
#define  NOP_EXPR 164 
#define  ORDERED_EXPR 163 
#define  PLUS_EXPR 162 
#define  POSTDECREMENT_EXPR 161 
#define  POSTINCREMENT_EXPR 160 
#define  PREDECREMENT_EXPR 159 
#define  PREINCREMENT_EXPR 158 
#define  RDIV_EXPR 157 
#define  REALPART_EXPR 156 
#define  REDUC_MAX_EXPR 155 
#define  REDUC_MIN_EXPR 154 
#define  REDUC_PLUS_EXPR 153 
#define  ROUND_DIV_EXPR 152 
#define  ROUND_MOD_EXPR 151 
#define  RROTATE_EXPR 150 
#define  RSHIFT_EXPR 149 
#define  SAVE_EXPR 148 
#define  TARGET_EXPR 147 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
#define  TREE_LIST 146 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  TRUNC_DIV_EXPR 145 
#define  TRUNC_MOD_EXPR 144 
#define  TRUTH_ANDIF_EXPR 143 
#define  TRUTH_AND_EXPR 142 
#define  TRUTH_NOT_EXPR 141 
#define  TRUTH_ORIF_EXPR 140 
#define  TRUTH_OR_EXPR 139 
#define  TRUTH_XOR_EXPR 138 
#define  UNEQ_EXPR 137 
#define  UNGE_EXPR 136 
#define  UNGT_EXPR 135 
#define  UNLE_EXPR 134 
#define  UNLT_EXPR 133 
#define  UNORDERED_EXPR 132 
#define  VEC_LSHIFT_EXPR 131 
#define  VEC_RSHIFT_EXPR 130 
#define  WIDEN_MULT_EXPR 129 
#define  WIDEN_SUM_EXPR 128 

__attribute__((used)) static int
op_prio (tree op)
{
  if (op == NULL)
    return 9999;

  switch (TREE_CODE (op))
    {
    case TREE_LIST:
    case COMPOUND_EXPR:
    case BIND_EXPR:
      return 1;

    case MODIFY_EXPR:
    case INIT_EXPR:
      return 2;

    case COND_EXPR:
      return 3;

    case TRUTH_OR_EXPR:
    case TRUTH_ORIF_EXPR:
      return 4;

    case TRUTH_AND_EXPR:
    case TRUTH_ANDIF_EXPR:
      return 5;

    case BIT_IOR_EXPR:
      return 6;

    case BIT_XOR_EXPR:
    case TRUTH_XOR_EXPR:
      return 7;

    case BIT_AND_EXPR:
      return 8;

    case EQ_EXPR:
    case NE_EXPR:
      return 9;

    case UNLT_EXPR:
    case UNLE_EXPR:
    case UNGT_EXPR:
    case UNGE_EXPR:
    case UNEQ_EXPR:
    case LTGT_EXPR:
    case ORDERED_EXPR:
    case UNORDERED_EXPR:
    case LT_EXPR:
    case LE_EXPR:
    case GT_EXPR:
    case GE_EXPR:
      return 10;

    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
    case LROTATE_EXPR:
    case RROTATE_EXPR:
      return 11;

    case WIDEN_SUM_EXPR:
    case PLUS_EXPR:
    case MINUS_EXPR:
      return 12;

    case WIDEN_MULT_EXPR:
    case DOT_PROD_EXPR:
    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
    case CEIL_DIV_EXPR:
    case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case RDIV_EXPR:
    case EXACT_DIV_EXPR:
    case TRUNC_MOD_EXPR:
    case CEIL_MOD_EXPR:
    case FLOOR_MOD_EXPR:
    case ROUND_MOD_EXPR:
      return 13;

    case TRUTH_NOT_EXPR:
    case BIT_NOT_EXPR:
    case POSTINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case PREINCREMENT_EXPR:
    case PREDECREMENT_EXPR:
    case NEGATE_EXPR:
    case ALIGN_INDIRECT_REF:
    case MISALIGNED_INDIRECT_REF:
    case INDIRECT_REF:
    case ADDR_EXPR:
    case FLOAT_EXPR:
    case NOP_EXPR:
    case CONVERT_EXPR:
    case FIX_TRUNC_EXPR:
    case FIX_CEIL_EXPR:
    case FIX_FLOOR_EXPR:
    case FIX_ROUND_EXPR:
    case TARGET_EXPR:
      return 14;

    case CALL_EXPR:
    case ARRAY_REF:
    case ARRAY_RANGE_REF:
    case COMPONENT_REF:
      return 15;

      /* Special expressions.  */
    case MIN_EXPR:
    case MAX_EXPR:
    case ABS_EXPR:
    case REALPART_EXPR:
    case IMAGPART_EXPR:
    case REDUC_MAX_EXPR:
    case REDUC_MIN_EXPR:
    case REDUC_PLUS_EXPR:
    case VEC_LSHIFT_EXPR:
    case VEC_RSHIFT_EXPR:
      return 16;

    case SAVE_EXPR:
    case NON_LVALUE_EXPR:
      return op_prio (TREE_OPERAND (op, 0));

    default:
      /* Return an arbitrarily high precedence to avoid surrounding single
	 VAR_DECLs in ()s.  */
      return 9999;
    }
}