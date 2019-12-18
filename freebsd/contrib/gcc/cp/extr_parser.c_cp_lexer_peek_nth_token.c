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
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_9__ {TYPE_1__* last_token; TYPE_1__* next_token; } ;
typedef  TYPE_2__ cp_lexer ;

/* Variables and functions */
 scalar_t__ CPP_PURGED ; 
 int /*<<< orphan*/  cp_lexer_debug_stream ; 
 scalar_t__ cp_lexer_debugging_p (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_lexer_print_token (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ eof_token ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cp_token *
cp_lexer_peek_nth_token (cp_lexer* lexer, size_t n)
{
  cp_token *token;

  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  if (cp_lexer_debugging_p (lexer))
    fprintf (cp_lexer_debug_stream,
	     "cp_lexer: peeking ahead %ld at token: ", (long)n);

  --n;
  token = lexer->next_token;
  gcc_assert (!n || token != &eof_token);
  while (n != 0)
    {
      ++token;
      if (token == lexer->last_token)
	{
	  token = (cp_token *)&eof_token;
	  break;
	}

      if (token->type != CPP_PURGED)
	--n;
    }

  if (cp_lexer_debugging_p (lexer))
    {
      cp_lexer_print_token (cp_lexer_debug_stream, token);
      putc ('\n', cp_lexer_debug_stream);
    }

  return token;
}