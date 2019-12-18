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
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_10__ {TYPE_1__* next_token; TYPE_1__* last_token; int /*<<< orphan*/  in_pragma; } ;
typedef  TYPE_2__ cp_lexer ;

/* Variables and functions */
 scalar_t__ CPP_PRAGMA_EOL ; 
 scalar_t__ CPP_PURGED ; 
 int /*<<< orphan*/  cp_lexer_debug_stream ; 
 scalar_t__ cp_lexer_debugging_p (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_lexer_print_token (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_lexer_set_source_position_from_token (TYPE_1__*) ; 
 TYPE_1__ eof_token ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cp_token *
cp_lexer_consume_token (cp_lexer* lexer)
{
  cp_token *token = lexer->next_token;

  gcc_assert (token != &eof_token);
  gcc_assert (!lexer->in_pragma || token->type != CPP_PRAGMA_EOL);

  do
    {
      lexer->next_token++;
      if (lexer->next_token == lexer->last_token)
	{
	  lexer->next_token = (cp_token *)&eof_token;
	  break;
	}

    }
  while (lexer->next_token->type == CPP_PURGED);

  cp_lexer_set_source_position_from_token (token);

  /* Provide debugging output.  */
  if (cp_lexer_debugging_p (lexer))
    {
      fputs ("cp_lexer: consuming token: ", cp_lexer_debug_stream);
      cp_lexer_print_token (cp_lexer_debug_stream, token);
      putc ('\n', cp_lexer_debug_stream);
    }

  return token;
}