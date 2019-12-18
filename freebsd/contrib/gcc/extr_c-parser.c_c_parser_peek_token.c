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
typedef  int /*<<< orphan*/  c_token ;
struct TYPE_4__ {int tokens_avail; int /*<<< orphan*/ * tokens; } ;
typedef  TYPE_1__ c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  c_lex_one_token (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static inline c_token *
c_parser_peek_token (c_parser *parser)
{
  if (parser->tokens_avail == 0)
    {
      /* APPLE LOCAL begin switch these two */
      parser->tokens_avail = 1;
      /* APPLE LOCAL C* language (in 4.2 ae) */
      c_lex_one_token (&parser->tokens[0], parser);
      /* APPLE LOCAL end switch these two */
    }
  return &parser->tokens[0];
}