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
typedef  int /*<<< orphan*/ * optab ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  ABS_EXPR 160 
#define  BIT_AND_EXPR 159 
#define  BIT_IOR_EXPR 158 
#define  BIT_NOT_EXPR 157 
#define  BIT_XOR_EXPR 156 
#define  CEIL_DIV_EXPR 155 
#define  CEIL_MOD_EXPR 154 
#define  DOT_PROD_EXPR 153 
#define  EXACT_DIV_EXPR 152 
#define  FLOOR_DIV_EXPR 151 
#define  FLOOR_MOD_EXPR 150 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
#define  LROTATE_EXPR 149 
#define  LSHIFT_EXPR 148 
#define  MAX_EXPR 147 
#define  MINUS_EXPR 146 
#define  MIN_EXPR 145 
#define  MULT_EXPR 144 
#define  NEGATE_EXPR 143 
#define  PLUS_EXPR 142 
#define  RDIV_EXPR 141 
#define  REALIGN_LOAD_EXPR 140 
#define  REDUC_MAX_EXPR 139 
#define  REDUC_MIN_EXPR 138 
#define  REDUC_PLUS_EXPR 137 
#define  ROUND_DIV_EXPR 136 
#define  ROUND_MOD_EXPR 135 
#define  RROTATE_EXPR 134 
#define  RSHIFT_EXPR 133 
#define  TRUNC_DIV_EXPR 132 
#define  TRUNC_MOD_EXPR 131 
 scalar_t__ TYPE_OVERFLOW_TRAPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  VEC_LSHIFT_EXPR 130 
#define  VEC_RSHIFT_EXPR 129 
#define  WIDEN_SUM_EXPR 128 
 int /*<<< orphan*/ * abs_optab ; 
 int /*<<< orphan*/ * absv_optab ; 
 int /*<<< orphan*/ * add_optab ; 
 int /*<<< orphan*/ * addv_optab ; 
 int /*<<< orphan*/ * and_optab ; 
 int /*<<< orphan*/ * ashl_optab ; 
 int /*<<< orphan*/ * ashr_optab ; 
 int /*<<< orphan*/ * ior_optab ; 
 int /*<<< orphan*/ * lshr_optab ; 
 int /*<<< orphan*/ * neg_optab ; 
 int /*<<< orphan*/ * negv_optab ; 
 int /*<<< orphan*/ * one_cmpl_optab ; 
 int /*<<< orphan*/ * reduc_smax_optab ; 
 int /*<<< orphan*/ * reduc_smin_optab ; 
 int /*<<< orphan*/ * reduc_splus_optab ; 
 int /*<<< orphan*/ * reduc_umax_optab ; 
 int /*<<< orphan*/ * reduc_umin_optab ; 
 int /*<<< orphan*/ * reduc_uplus_optab ; 
 int /*<<< orphan*/ * rotl_optab ; 
 int /*<<< orphan*/ * rotr_optab ; 
 int /*<<< orphan*/ * sdiv_optab ; 
 int /*<<< orphan*/ * sdot_prod_optab ; 
 int /*<<< orphan*/ * smax_optab ; 
 int /*<<< orphan*/ * smin_optab ; 
 int /*<<< orphan*/ * smod_optab ; 
 int /*<<< orphan*/ * smul_optab ; 
 int /*<<< orphan*/ * smulv_optab ; 
 int /*<<< orphan*/ * ssum_widen_optab ; 
 int /*<<< orphan*/ * sub_optab ; 
 int /*<<< orphan*/ * subv_optab ; 
 int /*<<< orphan*/ * udiv_optab ; 
 int /*<<< orphan*/ * udot_prod_optab ; 
 int /*<<< orphan*/ * umax_optab ; 
 int /*<<< orphan*/ * umin_optab ; 
 int /*<<< orphan*/ * umod_optab ; 
 int /*<<< orphan*/ * usum_widen_optab ; 
 int /*<<< orphan*/ * vec_realign_load_optab ; 
 int /*<<< orphan*/ * vec_shl_optab ; 
 int /*<<< orphan*/ * vec_shr_optab ; 
 int /*<<< orphan*/ * xor_optab ; 

optab
optab_for_tree_code (enum tree_code code, tree type)
{
  bool trapv;
  switch (code)
    {
    case BIT_AND_EXPR:
      return and_optab;

    case BIT_IOR_EXPR:
      return ior_optab;

    case BIT_NOT_EXPR:
      return one_cmpl_optab;

    case BIT_XOR_EXPR:
      return xor_optab;

    case TRUNC_MOD_EXPR:
    case CEIL_MOD_EXPR:
    case FLOOR_MOD_EXPR:
    case ROUND_MOD_EXPR:
      return TYPE_UNSIGNED (type) ? umod_optab : smod_optab;

    case RDIV_EXPR:
    case TRUNC_DIV_EXPR:
    case CEIL_DIV_EXPR:
    case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case EXACT_DIV_EXPR:
      return TYPE_UNSIGNED (type) ? udiv_optab : sdiv_optab;

    case LSHIFT_EXPR:
      return ashl_optab;

    case RSHIFT_EXPR:
      return TYPE_UNSIGNED (type) ? lshr_optab : ashr_optab;

    case LROTATE_EXPR:
      return rotl_optab;

    case RROTATE_EXPR:
      return rotr_optab;

    case MAX_EXPR:
      return TYPE_UNSIGNED (type) ? umax_optab : smax_optab;

    case MIN_EXPR:
      return TYPE_UNSIGNED (type) ? umin_optab : smin_optab;

    case REALIGN_LOAD_EXPR:
      return vec_realign_load_optab;

    case WIDEN_SUM_EXPR:
      return TYPE_UNSIGNED (type) ? usum_widen_optab : ssum_widen_optab;

    case DOT_PROD_EXPR:
      return TYPE_UNSIGNED (type) ? udot_prod_optab : sdot_prod_optab;

    case REDUC_MAX_EXPR:
      return TYPE_UNSIGNED (type) ? reduc_umax_optab : reduc_smax_optab;

    case REDUC_MIN_EXPR:
      return TYPE_UNSIGNED (type) ? reduc_umin_optab : reduc_smin_optab;

    case REDUC_PLUS_EXPR:
      return TYPE_UNSIGNED (type) ? reduc_uplus_optab : reduc_splus_optab;

    case VEC_LSHIFT_EXPR:
      return vec_shl_optab;

    case VEC_RSHIFT_EXPR:
      return vec_shr_optab;

    default:
      break;
    }

  trapv = INTEGRAL_TYPE_P (type) && TYPE_OVERFLOW_TRAPS (type);
  switch (code)
    {
    case PLUS_EXPR:
      return trapv ? addv_optab : add_optab;

    case MINUS_EXPR:
      return trapv ? subv_optab : sub_optab;

    case MULT_EXPR:
      return trapv ? smulv_optab : smul_optab;

    case NEGATE_EXPR:
      return trapv ? negv_optab : neg_optab;

    case ABS_EXPR:
      return trapv ? absv_optab : abs_optab;

    default:
      return NULL;
    }
}