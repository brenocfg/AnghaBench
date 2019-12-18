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
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_LESS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 scalar_t__ CPP_SEMICOLON ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_AT_END ; 
 int /*<<< orphan*/  RID_AT_PROTOCOL ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_interfacedecllist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_protocol_refs (int /*<<< orphan*/ *) ; 
 TYPE_2__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  chainon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_declare_protocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_finish_interface () ; 
 int objc_pq_context ; 
 int /*<<< orphan*/  objc_start_protocol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
/* APPLE LOCAL radar 4947311 - protocol attributes */
c_parser_objc_protocol_definition (c_parser *parser, tree attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));
  c_parser_consume_token (parser);
  if (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      return;
    }
  if (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      tree list = NULL_TREE;
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      while (true)
	{
	  tree id;
	  if (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      break;
	    }
	  id = c_parser_peek_token (parser)->value;
	  list = chainon (list, build_tree_list (NULL_TREE, id));
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  else
	    break;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      /* APPLE LOCAL radar 4947311 - protocol attributes */
      objc_declare_protocols (list, attributes);
    }
  else
    {
      tree id = c_parser_peek_token (parser)->value;
      tree proto = NULL_TREE;
      c_parser_consume_token (parser);
      if (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_pq_context = 1;
      /* APPLE LOCAL radar 4947311 - protocol attributes */
      objc_start_protocol (id, proto, attributes);
      /* APPLE LOCAL C* property (Radar 4436866) (in 4.2 r) */
      c_parser_objc_interfacedecllist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_pq_context = 0;
      objc_finish_interface ();
    }
}