#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cp_token ;
struct TYPE_7__ {TYPE_1__* lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_6__ {int in_pragma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_PRAGMA_EOL ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_pragma_eol (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cp_parser_require_pragma_eol (cp_parser *parser, cp_token *pragma_tok)
{
  parser->lexer->in_pragma = false;
  if (!cp_parser_require (parser, CPP_PRAGMA_EOL, "end of line"))
    cp_parser_skip_to_pragma_eol (parser, pragma_tok);
}