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
typedef  scalar_t__ tree ;
struct TYPE_4__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
typedef  scalar_t__ TREE_CHAIN ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMA ; 
 scalar_t__ DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_mem_initializer (TYPE_1__*) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_mem_initializers (scalar_t__) ; 

__attribute__((used)) static void
cp_parser_mem_initializer_list (cp_parser* parser)
{
  tree mem_initializer_list = NULL_TREE;

  /* Let the semantic analysis code know that we are starting the
     mem-initializer-list.  */
  if (!DECL_CONSTRUCTOR_P (current_function_decl))
    error ("only constructors take base initializers");

  /* Loop through the list.  */
  while (true)
    {
      tree mem_initializer;

      /* Parse the mem-initializer.  */
      mem_initializer = cp_parser_mem_initializer (parser);
      /* Add it to the list, unless it was erroneous.  */
      if (mem_initializer != error_mark_node)
	{
	  TREE_CHAIN (mem_initializer) = mem_initializer_list;
	  mem_initializer_list = mem_initializer;
	}
      /* If the next token is not a `,', we're done.  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	break;
      /* Consume the `,' token.  */
      cp_lexer_consume_token (parser->lexer);
    }

  /* Perform semantic analysis.  */
  if (DECL_CONSTRUCTOR_P (current_function_decl))
    finish_mem_initializers (mem_initializer_list);
}