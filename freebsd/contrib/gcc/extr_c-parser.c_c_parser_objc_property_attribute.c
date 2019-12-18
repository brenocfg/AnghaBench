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
struct TYPE_2__ {scalar_t__ type; int keyword; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COLON ; 
 scalar_t__ CPP_KEYWORD ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_GETTER 131 
#define  RID_NONATOMIC 130 
#define  RID_READONLY 129 
#define  RID_SETTER 128 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_eq_identifier (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objc_set_property_attr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
c_parser_objc_property_attribute (c_parser *parser)
{
  tree id;
  if (c_parser_peek_token (parser)->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected a property attribute");
      c_parser_consume_token (parser);
      return;
    }
  switch (c_parser_peek_token (parser)->keyword)
    {
    case RID_READONLY:
      c_parser_consume_token (parser);
      objc_set_property_attr (1, NULL_TREE);
      break;
    case RID_GETTER:
      c_parser_consume_token (parser);
      id = c_parser_objc_eq_identifier (parser);
      if (id)
	objc_set_property_attr (2, id);
      break;
    case RID_SETTER:
      c_parser_consume_token (parser);
      id = c_parser_objc_eq_identifier (parser);
      if (id)
	objc_set_property_attr (3, id);
      /* Consume the ':' which must always follow the setter name. */
      if (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      break;
   /* APPLE LOCAL begin radar 4947014 - objc atomic property */
    case RID_NONATOMIC:
      c_parser_consume_token (parser);
      objc_set_property_attr (13, NULL_TREE);
      break;
    /* APPLE LOCAL end radar 4947014 - objc atomic property */
    default:
      c_parser_error (parser, "expected a property attribute");
      c_parser_consume_token (parser);
    }
}