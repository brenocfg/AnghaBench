#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COLON ; 
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_mem_initializer_list (TYPE_1__*) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  finish_mem_initializers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cp_parser_ctor_initializer_opt (cp_parser* parser)
{
  /* If the next token is not a `:', then there is no
     ctor-initializer.  */
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_COLON))
    {
      /* Do default initialization of any bases and members.  */
      if (DECL_CONSTRUCTOR_P (current_function_decl))
	finish_mem_initializers (NULL_TREE);

      return false;
    }

  /* Consume the `:' token.  */
  cp_lexer_consume_token (parser->lexer);
  /* And the mem-initializer-list.  */
  cp_parser_mem_initializer_list (parser);

  return true;
}