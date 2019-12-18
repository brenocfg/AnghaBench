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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_EQ ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
c_parser_objc_eq_identifier (c_parser *parser)
{
  tree id;
  if (c_parser_next_token_is_not (parser, CPP_EQ))
    {
      c_parser_error (parser, "expected %<=%>");
      return NULL_TREE;
    }
  /* Consume '=' */
  c_parser_consume_token (parser);
  if (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      return NULL_TREE;
    }
  id = c_parser_peek_token (parser)->value;
  c_parser_consume_token (parser);
  return id;
}