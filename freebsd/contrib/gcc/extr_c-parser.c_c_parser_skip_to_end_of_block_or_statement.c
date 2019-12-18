#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; } ;
typedef  TYPE_1__ c_token ;
struct TYPE_10__ {int error; int /*<<< orphan*/  in_pragma; } ;
typedef  TYPE_2__ c_parser ;

/* Variables and functions */
#define  CPP_CLOSE_BRACE 133 
#define  CPP_EOF 132 
#define  CPP_OPEN_BRACE 131 
#define  CPP_PRAGMA 130 
#define  CPP_PRAGMA_EOL 129 
#define  CPP_SEMICOLON 128 
 int /*<<< orphan*/  c_parser_consume_pragma (TYPE_2__*) ; 
 int /*<<< orphan*/  c_parser_consume_token (TYPE_2__*) ; 
 TYPE_1__* c_parser_peek_token (TYPE_2__*) ; 
 int /*<<< orphan*/  c_parser_skip_to_pragma_eol (TYPE_2__*) ; 

__attribute__((used)) static void
c_parser_skip_to_end_of_block_or_statement (c_parser *parser)
{
  unsigned nesting_depth = 0;
  bool save_error = parser->error;

  while (true)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      switch (token->type)
	{
	case CPP_EOF:
	  return;

	case CPP_PRAGMA_EOL:
	  if (parser->in_pragma)
	    return;
	  break;

	case CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  if (!nesting_depth)
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      goto finished;
	    }
	  break;

	case CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  if (nesting_depth == 0 || --nesting_depth == 0)
	    {
	      c_parser_consume_token (parser);
	      goto finished;
	    }
	  break;

	case CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  break;

	case CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  parser->error = save_error;
	  continue;

	default:
	  break;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = false;
}