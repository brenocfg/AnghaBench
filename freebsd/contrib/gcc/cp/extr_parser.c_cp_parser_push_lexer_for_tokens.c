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
typedef  int /*<<< orphan*/  cp_token_cache ;
struct TYPE_5__ {TYPE_2__* lexer; } ;
typedef  TYPE_1__ cp_parser ;
struct TYPE_6__ {int /*<<< orphan*/  next_token; struct TYPE_6__* next; } ;
typedef  TYPE_2__ cp_lexer ;

/* Variables and functions */
 TYPE_2__* cp_lexer_new_from_tokens (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_lexer_set_source_position_from_token (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_push_lexer_for_tokens (cp_parser *parser, cp_token_cache *cache)
{
  cp_lexer *lexer = cp_lexer_new_from_tokens (cache);
  lexer->next = parser->lexer;
  parser->lexer = lexer;

  /* Move the current source position to that of the first token in the
     new lexer.  */
  cp_lexer_set_source_position_from_token (lexer->next_token);
}