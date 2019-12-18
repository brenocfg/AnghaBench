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
#define  CPP_CLOSE_BRACE 132 
#define  CPP_EOF 131 
#define  CPP_OPEN_BRACE 130 
#define  CPP_PRAGMA_EOL 129 
#define  CPP_SEMICOLON 128 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_skip_to_end_of_block_or_statement (cp_parser* parser)
{
  int nesting_depth = 0;

  while (nesting_depth >= 0)
    {
      cp_token *token = cp_lexer_peek_token (parser->lexer);

      switch (token->type)
	{
	case CPP_EOF:
	case CPP_PRAGMA_EOL:
	  /* If we've run out of tokens, stop.  */
	  return;

	case CPP_SEMICOLON:
	  /* Stop if this is an unnested ';'. */
	  if (!nesting_depth)
	    nesting_depth = -1;
	  break;

	case CPP_CLOSE_BRACE:
	  /* Stop if this is an unnested '}', or closes the outermost
	     nesting level.  */
	  nesting_depth--;
	  if (!nesting_depth)
	    nesting_depth = -1;
	  break;

	case CPP_OPEN_BRACE:
	  /* Nest. */
	  nesting_depth++;
	  break;

	default:
	  break;
	}

      /* Consume the token.  */
      cp_lexer_consume_token (parser->lexer);
    }
}