#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_10__ {TYPE_5__* lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_11__ {int in_pragma; } ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_PRAGMA_EOL ; 
 TYPE_1__* cp_lexer_consume_token (TYPE_5__*) ; 
 int /*<<< orphan*/  cp_lexer_purge_tokens_after (TYPE_5__*,TYPE_1__*) ; 

__attribute__((used)) static void
cp_parser_skip_to_pragma_eol (cp_parser* parser, cp_token *pragma_tok)
{
  cp_token *token;

  parser->lexer->in_pragma = false;

  do
    token = cp_lexer_consume_token (parser->lexer);
  while (token->type != CPP_PRAGMA_EOL && token->type != CPP_EOF);

  /* Ensure that the pragma is not parsed again.  */
  cp_lexer_purge_tokens_after (parser->lexer, pragma_tok);
}