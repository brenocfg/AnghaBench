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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_enumerator_definition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_system_header ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 

__attribute__((used)) static void
cp_parser_enumerator_list (cp_parser* parser, tree type)
{
  while (true)
    {
      /* Parse an enumerator-definition.  */
      cp_parser_enumerator_definition (parser, type);

      /* If the next token is not a ',', we've reached the end of
	 the list.  */
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	break;
      /* Otherwise, consume the `,' and keep going.  */
      cp_lexer_consume_token (parser->lexer);
      /* If the next token is a `}', there is a trailing comma.  */
      if (cp_lexer_next_token_is (parser->lexer, CPP_CLOSE_BRACE))
	{
	  if (pedantic && !in_system_header)
	    pedwarn ("comma at end of enumerator list");
	  break;
	}
    }
}