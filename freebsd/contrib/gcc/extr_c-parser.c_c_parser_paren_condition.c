#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_objc_common_truthvalue_conversion (int /*<<< orphan*/ ) ; 
 TYPE_2__ c_parser_expression_conv (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
c_parser_paren_condition (c_parser *parser)
{
  location_t loc;
  tree cond;
  if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    return error_mark_node;
  loc = c_parser_peek_token (parser)->location;
  cond = c_objc_common_truthvalue_conversion
    (c_parser_expression_conv (parser).value);
  if (EXPR_P (cond))
    SET_EXPR_LOCATION (cond, loc);
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
  return cond;
}