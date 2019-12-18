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
 int /*<<< orphan*/  RID_EXPORT ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_template_declaration_after_export (TYPE_1__*,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cp_parser_template_declaration (cp_parser* parser, bool member_p)
{
  /* Check for `export'.  */
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_EXPORT))
    {
      /* Consume the `export' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Warn that we do not support `export'.  */
      warning (0, "keyword %<export%> not implemented, and will be ignored");
    }

  cp_parser_template_declaration_after_export (parser, member_p);
}