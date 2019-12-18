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
typedef  char* tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  BIT_AND_EXPR 149 
#define  BIT_IOR_EXPR 148 
#define  BIT_XOR_EXPR 147 
#define  EQ_EXPR 146 
#define  FLOOR_DIV_EXPR 145 
#define  FLOOR_MOD_EXPR 144 
#define  GE_EXPR 143 
#define  GT_EXPR 142 
#define  LE_EXPR 141 
#define  LSHIFT_EXPR 140 
#define  LT_EXPR 139 
#define  MAX_EXPR 138 
#define  MINUS_EXPR 137 
#define  MIN_EXPR 136 
#define  MULT_EXPR 135 
#define  NE_EXPR 134 
#define  PLUS_EXPR 133 
#define  RSHIFT_EXPR 132 
#define  TRUNC_DIV_EXPR 131 
#define  TRUNC_MOD_EXPR 130 
#define  TRUTH_ANDIF_EXPR 129 
#define  TRUTH_ORIF_EXPR 128 
 int /*<<< orphan*/  error (char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

void
binary_op_error (enum tree_code code, tree type0, tree type1)
{
  const char *opname;

  switch (code)
    {
    case PLUS_EXPR:
      opname = "+"; break;
    case MINUS_EXPR:
      opname = "-"; break;
    case MULT_EXPR:
      opname = "*"; break;
    case MAX_EXPR:
      opname = "max"; break;
    case MIN_EXPR:
      opname = "min"; break;
    case EQ_EXPR:
      opname = "=="; break;
    case NE_EXPR:
      opname = "!="; break;
    case LE_EXPR:
      opname = "<="; break;
    case GE_EXPR:
      opname = ">="; break;
    case LT_EXPR:
      opname = "<"; break;
    case GT_EXPR:
      opname = ">"; break;
    case LSHIFT_EXPR:
      opname = "<<"; break;
    case RSHIFT_EXPR:
      opname = ">>"; break;
    case TRUNC_MOD_EXPR:
    case FLOOR_MOD_EXPR:
      opname = "%"; break;
    case TRUNC_DIV_EXPR:
    case FLOOR_DIV_EXPR:
      opname = "/"; break;
    case BIT_AND_EXPR:
      opname = "&"; break;
    case BIT_IOR_EXPR:
      opname = "|"; break;
    case TRUTH_ANDIF_EXPR:
      opname = "&&"; break;
    case TRUTH_ORIF_EXPR:
      opname = "||"; break;
    case BIT_XOR_EXPR:
      opname = "^"; break;
    default:
      gcc_unreachable ();
    }
  error ("invalid operands to binary %s (have %qT and %qT)", opname,
	 type0, type1);
}