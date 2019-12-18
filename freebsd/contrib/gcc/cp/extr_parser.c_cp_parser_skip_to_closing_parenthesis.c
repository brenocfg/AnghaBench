#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_7__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
#define  CPP_CLOSE_BRACE 135 
#define  CPP_CLOSE_PAREN 134 
#define  CPP_COMMA 133 
#define  CPP_EOF 132 
#define  CPP_OPEN_BRACE 131 
#define  CPP_OPEN_PAREN 130 
#define  CPP_PRAGMA_EOL 129 
#define  CPP_SEMICOLON 128 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_uncommitted_to_tentative_parse_p (TYPE_2__*) ; 

__attribute__((used)) static int
cp_parser_skip_to_closing_parenthesis (cp_parser *parser,
				       bool recovering,
				       bool or_comma,
				       bool consume_paren)
{
  unsigned paren_depth = 0;
  unsigned brace_depth = 0;

  if (recovering && !or_comma
      && cp_parser_uncommitted_to_tentative_parse_p (parser))
    return 0;

  while (true)
    {
      cp_token * token = cp_lexer_peek_token (parser->lexer);

      switch (token->type)
	{
	case CPP_EOF:
	case CPP_PRAGMA_EOL:
	  /* If we've run out of tokens, then there is no closing `)'.  */
	  return 0;

	case CPP_SEMICOLON:
	  /* This matches the processing in skip_to_end_of_statement.  */
	  if (!brace_depth)
	    return 0;
	  break;

	case CPP_OPEN_BRACE:
	  ++brace_depth;
	  break;
	case CPP_CLOSE_BRACE:
	  if (!brace_depth--)
	    return 0;
	  break;

	case CPP_COMMA:
	  if (recovering && or_comma && !brace_depth && !paren_depth)
	    return -1;
	  break;

	case CPP_OPEN_PAREN:
	  if (!brace_depth)
	    ++paren_depth;
	  break;

	case CPP_CLOSE_PAREN:
	  if (!brace_depth && !paren_depth--)
	    {
	      if (consume_paren)
		cp_lexer_consume_token (parser->lexer);
	      return 1;
	    }
	  break;

	default:
	  break;
	}

      /* Consume the token.  */
      cp_lexer_consume_token (parser->lexer);
    }
}