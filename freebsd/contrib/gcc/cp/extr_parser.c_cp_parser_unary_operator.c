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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ cp_token ;

/* Variables and functions */
 int ADDR_EXPR ; 
 int BIT_NOT_EXPR ; 
#define  CPP_AND 133 
#define  CPP_COMPL 132 
#define  CPP_MINUS 131 
#define  CPP_MULT 130 
#define  CPP_NOT 129 
#define  CPP_PLUS 128 
 int ERROR_MARK ; 
 int INDIRECT_REF ; 
 int NEGATE_EXPR ; 
 int TRUTH_NOT_EXPR ; 
 int UNARY_PLUS_EXPR ; 

__attribute__((used)) static enum tree_code
cp_parser_unary_operator (cp_token* token)
{
  switch (token->type)
    {
    case CPP_MULT:
      return INDIRECT_REF;

    case CPP_AND:
      return ADDR_EXPR;

    case CPP_PLUS:
      return UNARY_PLUS_EXPR;

    case CPP_MINUS:
      return NEGATE_EXPR;

    case CPP_NOT:
      return TRUTH_NOT_EXPR;

    case CPP_COMPL:
      return BIT_NOT_EXPR;

    default:
      return ERROR_MARK;
    }
}