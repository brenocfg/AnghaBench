#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_6__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 int BIT_AND_EXPR ; 
 int BIT_IOR_EXPR ; 
 int BIT_XOR_EXPR ; 
#define  CPP_AND_EQ 138 
#define  CPP_DIV_EQ 137 
#define  CPP_EQ 136 
#define  CPP_LSHIFT_EQ 135 
#define  CPP_MINUS_EQ 134 
#define  CPP_MOD_EQ 133 
#define  CPP_MULT_EQ 132 
#define  CPP_OR_EQ 131 
#define  CPP_PLUS_EQ 130 
#define  CPP_RSHIFT_EQ 129 
#define  CPP_XOR_EQ 128 
 int ERROR_MARK ; 
 int LSHIFT_EXPR ; 
 int MINUS_EXPR ; 
 int MULT_EXPR ; 
 int NOP_EXPR ; 
 int PLUS_EXPR ; 
 int RSHIFT_EXPR ; 
 int TRUNC_DIV_EXPR ; 
 int TRUNC_MOD_EXPR ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum tree_code
cp_parser_assignment_operator_opt (cp_parser* parser)
{
  enum tree_code op;
  cp_token *token;

  /* Peek at the next toen.  */
  token = cp_lexer_peek_token (parser->lexer);

  switch (token->type)
    {
    case CPP_EQ:
      op = NOP_EXPR;
      break;

    case CPP_MULT_EQ:
      op = MULT_EXPR;
      break;

    case CPP_DIV_EQ:
      op = TRUNC_DIV_EXPR;
      break;

    case CPP_MOD_EQ:
      op = TRUNC_MOD_EXPR;
      break;

    case CPP_PLUS_EQ:
      op = PLUS_EXPR;
      break;

    case CPP_MINUS_EQ:
      op = MINUS_EXPR;
      break;

    case CPP_RSHIFT_EQ:
      op = RSHIFT_EXPR;
      break;

    case CPP_LSHIFT_EQ:
      op = LSHIFT_EXPR;
      break;

    case CPP_AND_EQ:
      op = BIT_AND_EXPR;
      break;

    case CPP_XOR_EQ:
      op = BIT_XOR_EXPR;
      break;

    case CPP_OR_EQ:
      op = BIT_IOR_EXPR;
      break;

    default:
      /* Nothing else is an assignment operator.  */
      op = ERROR_MARK;
    }

  /* If it was an assignment operator, consume it.  */
  if (op != ERROR_MARK)
    cp_lexer_consume_token (parser->lexer);

  return op;
}