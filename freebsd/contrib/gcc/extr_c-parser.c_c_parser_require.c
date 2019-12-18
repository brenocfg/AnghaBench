#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
c_parser_require (c_parser *parser,
		  enum cpp_ttype type,
		  const char *msgid)
{
  if (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      return true;
    }
  else
    {
      c_parser_error (parser, msgid);
      return false;
    }
}