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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  ADDR_EXPR 185 
#define  ALIGN_INDIRECT_REF 184 
#define  BIT_AND_EXPR 183 
#define  BIT_IOR_EXPR 182 
#define  BIT_NOT_EXPR 181 
#define  BIT_XOR_EXPR 180 
#define  CEIL_DIV_EXPR 179 
#define  CEIL_MOD_EXPR 178 
#define  EQ_EXPR 177 
#define  EXACT_DIV_EXPR 176 
#define  FLOOR_DIV_EXPR 175 
#define  FLOOR_MOD_EXPR 174 
#define  GE_EXPR 173 
#define  GT_EXPR 172 
#define  INDIRECT_REF 171 
#define  LE_EXPR 170 
#define  LROTATE_EXPR 169 
#define  LSHIFT_EXPR 168 
#define  LTGT_EXPR 167 
#define  LT_EXPR 166 
#define  MAX_EXPR 165 
#define  MINUS_EXPR 164 
#define  MIN_EXPR 163 
#define  MISALIGNED_INDIRECT_REF 162 
#define  MODIFY_EXPR 161 
#define  MULT_EXPR 160 
#define  NEGATE_EXPR 159 
#define  NE_EXPR 158 
#define  ORDERED_EXPR 157 
#define  PLUS_EXPR 156 
#define  POSTDECREMENT_EXPR 155 
#define  POSTINCREMENT_EXPR 154 
#define  PREDECREMENT_EXPR 153 
#define  PREINCREMENT_EXPR 152 
#define  RDIV_EXPR 151 
#define  REDUC_PLUS_EXPR 150 
#define  ROUND_DIV_EXPR 149 
#define  ROUND_MOD_EXPR 148 
#define  RROTATE_EXPR 147 
#define  RSHIFT_EXPR 146 
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

__attribute__((used)) static const char *
op_symbol_1 (enum tree_code code)
{
  switch (code)
    {
    case MODIFY_EXPR:
      return "=";

    case TRUTH_OR_EXPR:
    case TRUTH_ORIF_EXPR:
      return "||";

    case TRUTH_AND_EXPR:
    case TRUTH_ANDIF_EXPR:
      return "&&";

    case BIT_IOR_EXPR:
      return "|";

    case TRUTH_XOR_EXPR:
    case BIT_XOR_EXPR:
      return "^";

    case ADDR_EXPR:
    case BIT_AND_EXPR:
      return "&";

    case ORDERED_EXPR:
      return "ord";
    case UNORDERED_EXPR:
      return "unord";

    case EQ_EXPR:
      return "==";
    case UNEQ_EXPR:
      return "u==";

    case NE_EXPR:
      return "!=";

    case LT_EXPR:
      return "<";
    case UNLT_EXPR:
      return "u<";

    case LE_EXPR:
      return "<=";
    case UNLE_EXPR:
      return "u<=";

    case GT_EXPR:
      return ">";
    case UNGT_EXPR:
      return "u>";

    case GE_EXPR:
      return ">=";
    case UNGE_EXPR:
      return "u>=";

    case LTGT_EXPR:
      return "<>";

    case LSHIFT_EXPR:
      return "<<";

    case RSHIFT_EXPR:
      return ">>";

    case LROTATE_EXPR:
      return "r<<";

    case RROTATE_EXPR:
      return "r>>";

    case VEC_LSHIFT_EXPR:
      return "v<<";

    case VEC_RSHIFT_EXPR:
      return "v>>";
 
    case PLUS_EXPR:
      return "+";

    case REDUC_PLUS_EXPR:
      return "r+";

    case WIDEN_SUM_EXPR:
      return "w+";

    case WIDEN_MULT_EXPR:
      return "w*";

    case NEGATE_EXPR:
    case MINUS_EXPR:
      return "-";

    case BIT_NOT_EXPR:
      return "~";

    case TRUTH_NOT_EXPR:
      return "!";

    case MULT_EXPR:
    case INDIRECT_REF:
      return "*";

    case ALIGN_INDIRECT_REF:
      return "A*";

    case MISALIGNED_INDIRECT_REF:
      return "M*";

    case TRUNC_DIV_EXPR:
    case RDIV_EXPR:
      return "/";

    case CEIL_DIV_EXPR:
      return "/[cl]";

    case FLOOR_DIV_EXPR:
      return "/[fl]";

    case ROUND_DIV_EXPR:
      return "/[rd]";

    case EXACT_DIV_EXPR:
      return "/[ex]";

    case TRUNC_MOD_EXPR:
      return "%";

    case CEIL_MOD_EXPR:
      return "%[cl]";

    case FLOOR_MOD_EXPR:
      return "%[fl]";

    case ROUND_MOD_EXPR:
      return "%[rd]";

    case PREDECREMENT_EXPR:
      return " --";

    case PREINCREMENT_EXPR:
      return " ++";

    case POSTDECREMENT_EXPR:
      return "-- ";

    case POSTINCREMENT_EXPR:
      return "++ ";

    case MAX_EXPR:
      return "max";

    case MIN_EXPR:
      return "min";

    default:
      return "<<< ??? >>>";
    }
}