#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ c_token ;
struct TYPE_9__ {int error; scalar_t__ in_pragma; } ;
typedef  TYPE_2__ c_parser ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_BRACE ; 
 scalar_t__ CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_CLOSE_SQUARE ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_OPEN_BRACE ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 scalar_t__ CPP_OPEN_SQUARE ; 
 scalar_t__ CPP_PRAGMA_EOL ; 
 int /*<<< orphan*/  c_parser_consume_token (TYPE_2__*) ; 
 TYPE_1__* c_parser_peek_token (TYPE_2__*) ; 
 scalar_t__ c_parser_require (TYPE_2__*,int,char const*) ; 

__attribute__((used)) static void
c_parser_skip_until_found (c_parser *parser,
			   enum cpp_ttype type,
			   const char *msgid)
{
  unsigned nesting_depth = 0;

  if (c_parser_require (parser, type, msgid))
    return;

  /* Skip tokens until the desired token is found.  */
  while (true)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      if (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  break;
	}

      /* If we've run out of tokens, stop.  */
      if (token->type == CPP_EOF)
	return;
      if (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	return;
      if (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      else if (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  if (nesting_depth-- == 0)
	    break;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = false;
}