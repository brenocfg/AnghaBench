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
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_6__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
#define  CPP_CLOSE_BRACE 131 
#define  CPP_EOF 130 
#define  CPP_OPEN_BRACE 129 
#define  CPP_PRAGMA_EOL 128 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_skip_to_closing_brace (cp_parser *parser)
{
  unsigned nesting_depth = 0;

  while (true)
    {
      cp_token *token = cp_lexer_peek_token (parser->lexer);

      switch (token->type)
	{
	case CPP_EOF:
	case CPP_PRAGMA_EOL:
	  /* If we've run out of tokens, stop.  */
	  return;

	case CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  if (nesting_depth-- == 0)
	    return;
	  break;

	case CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  break;

	default:
	  break;
	}

      /* Consume the token.  */
      cp_lexer_consume_token (parser->lexer);
    }
}