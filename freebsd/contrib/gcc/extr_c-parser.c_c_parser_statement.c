#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_COLON ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  RID_CASE ; 
 int /*<<< orphan*/  RID_DEFAULT ; 
 int /*<<< orphan*/  c_parser_label (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_statement_after_labels (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
c_parser_statement (c_parser *parser)
{
  while (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    c_parser_label (parser);
  c_parser_statement_after_labels (parser);
}