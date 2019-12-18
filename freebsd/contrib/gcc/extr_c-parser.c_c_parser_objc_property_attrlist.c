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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_EOF ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_property_attribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
c_parser_objc_property_attrlist (c_parser *parser)
{
  while (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN)
	 && c_parser_next_token_is_not (parser, CPP_EOF))
    {
      c_parser_objc_property_attribute (parser);
      /* APPLE LOCAL begin radar 6302949 */
      if (c_parser_next_token_is_not (parser, CPP_COMMA)
	  && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN)
	  && c_parser_next_token_is_not (parser, CPP_EOF))
	warning (0, "property attributes must be separated by a comma");
      /* APPLE LOCAL end radar 6302949 */
      if (c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_NAME) /* error */)
	c_parser_consume_token (parser);
    }
}