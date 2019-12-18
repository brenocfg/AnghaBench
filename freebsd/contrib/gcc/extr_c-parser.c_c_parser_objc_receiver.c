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
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ id_kind; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ CPP_NAME ; 
 scalar_t__ C_ID_CLASSNAME ; 
 scalar_t__ C_ID_TYPENAME ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 TYPE_2__ c_parser_expression (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objc_get_class_reference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
c_parser_objc_receiver (c_parser *parser)
{
  if (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      tree id = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
      return objc_get_class_reference (id);
    }
  return c_parser_expression (parser).value;
}