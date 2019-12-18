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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_COLON ; 
 int /*<<< orphan*/  CPP_LESS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_AT_END ; 
 int /*<<< orphan*/  RID_AT_IMPLEMENTATION ; 
 int /*<<< orphan*/  RID_AT_INTERFACE ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_class_instance_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_interfacedecllist (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_objc_protocol_refs (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  objc_continue_implementation () ; 
 int /*<<< orphan*/  objc_continue_interface () ; 
 int /*<<< orphan*/  objc_finish_interface () ; 
 int /*<<< orphan*/  objc_start_category_implementation (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  objc_start_category_interface (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  objc_start_class_implementation (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  objc_start_class_interface (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
/* APPLE LOCAL radar 4548636 - class attributes. */
c_parser_objc_class_definition (c_parser *parser, tree prefix_attrs)
{
  bool iface_p;
  tree id1;
  tree superclass;
  if (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = true;
  else if (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    /* APPLE LOCAL begin radar 4548636 - class attributes. */
    {
      if (prefix_attrs)
	{
	  error ("attributes may not be specified on an implementation");
	  prefix_attrs = NULL_TREE;
	}
      iface_p = false;
    }
    /* APPLE LOCAL end radar 4548636 - class attributes. */
  else
    gcc_unreachable ();
  c_parser_consume_token (parser);
  if (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      /* APPLE LOCAL radar 4965989 */
      tree id2 = NULL_TREE;
      tree proto = NULL_TREE;
      c_parser_consume_token (parser);
      /* APPLE LOCAL begin radar 4965989 */
      if (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	   if (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
	      return;
	    }
	   id2 = c_parser_peek_token (parser)->value;
	   c_parser_consume_token (parser);
	}
      /* APPLE LOCAL end radar 4965989 */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      if (!iface_p)
	{
	   /* APPLE LOCAL begin radar 4965989 */
	  if (id2 == NULL_TREE)
	    {
	      error ("cannot implement anonymous category");
	      return;
	    }
	   /* APPLE LOCAL end radar 4965989 */
	  objc_start_category_implementation (id1, id2);
	  return;
	}
      if (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      /* APPLE LOCAL begin radar 4548636 - class attributes. */
      if (prefix_attrs)
	error ("attributes may not be specified on a category");
      /* APPLE LOCAL end radar 4548636 - class attributes. */
      objc_start_category_interface (id1, id2, proto);
      /* APPLE LOCAL C* property (Radar 4436866) (in 4.2 q) */
      c_parser_objc_interfacedecllist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      return;
    }
  if (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      if (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  return;
	}
      superclass = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
    }
  else
    superclass = NULL_TREE;
  if (iface_p)
    {
      tree proto = NULL_TREE;
      if (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      /* APPLE LOCAL radar 4548636 - class attributes. */
      objc_start_class_interface (id1, superclass, proto, prefix_attrs);
    }
  else
    objc_start_class_implementation (id1, superclass);
  if (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  if (iface_p)
    {
      objc_continue_interface ();
      /* APPLE LOCAL C* property (Radar 4436866) (in 4.2 q) */
      c_parser_objc_interfacedecllist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  else
    {
      objc_continue_implementation ();
      return;
    }
}