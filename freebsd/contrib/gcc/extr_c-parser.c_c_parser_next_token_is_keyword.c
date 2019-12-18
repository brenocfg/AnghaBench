#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_3__ {int keyword; } ;
typedef  TYPE_1__ c_token ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
c_parser_next_token_is_keyword (c_parser *parser, enum rid keyword)
{
  c_token *token;

  /* Peek at the next token.  */
  token = c_parser_peek_token (parser);
  /* Check to see if it is the indicated keyword.  */
  return token->keyword == keyword;
}