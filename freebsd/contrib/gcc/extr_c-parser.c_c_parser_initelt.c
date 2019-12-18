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
typedef  void* tree ;
struct c_expr {void* original_code; void* value; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; scalar_t__ id_kind; void* value; } ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_SQUARE ; 
 scalar_t__ CPP_COLON ; 
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_DOT ; 
 scalar_t__ CPP_ELLIPSIS ; 
 scalar_t__ CPP_EQ ; 
 scalar_t__ CPP_NAME ; 
 scalar_t__ CPP_OPEN_SQUARE ; 
 scalar_t__ C_ID_CLASSNAME ; 
 scalar_t__ C_ID_TYPENAME ; 
 void* ERROR_MARK ; 
 void* NULL_TREE ; 
 void* build_compound_expr (void*,void*) ; 
 int /*<<< orphan*/  build_tree_list (void*,void*) ; 
 scalar_t__ c_dialect_objc () ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 struct c_expr c_parser_expr_no_commas (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_initval (int /*<<< orphan*/ *,struct c_expr*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,scalar_t__) ; 
 void* c_parser_objc_message_args (int /*<<< orphan*/ *) ; 
 TYPE_2__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 
 void* error_mark_node ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 void* objc_build_message_expr (int /*<<< orphan*/ ) ; 
 void* objc_get_class_reference (void*) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  process_init_element (struct c_expr) ; 
 int /*<<< orphan*/  set_init_index (void*,void*) ; 
 int /*<<< orphan*/  set_init_label (void*) ; 

__attribute__((used)) static void
c_parser_initelt (c_parser *parser)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  if (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->value);
      if (pedantic)
	pedwarn ("obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  else
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      int des_seen = 0;
      while (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  int des_prev = des_seen;
	  if (des_seen < 2)
	    des_seen++;
	  if (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      if (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (c_parser_peek_token (parser)->value);
		  c_parser_consume_token (parser);
		}
	      else
		{
		  struct c_expr init;
		  init.value = error_mark_node;
		  init.original_code = ERROR_MARK;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, NULL);
		  process_init_element (init);
		  return;
		}
	    }
	  else
	    {
	      tree first, second;
	      /* ??? Following the old parser, [ objc-receiver
		 objc-message-args ] is accepted as an initializer,
		 being distinguished from a designator by what follows
		 the first assignment expression inside the square
		 brackets, but after a first array designator a
		 subsequent square bracket is for Objective-C taken to
		 start an expression, using the obsolete form of
		 designated initializer without '=', rather than
		 possibly being a second level of designation: in LALR
		 terms, the '[' is shifted rather than reducing
		 designator to designator-list.  */
	      if (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  break;
		}
	      if (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  tree rec, args;
		  struct c_expr mexpr;
		  c_parser_consume_token (parser);
		  if (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      tree id = c_parser_peek_token (parser)->value;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      goto parse_message_args;
		    }
		  first = c_parser_expr_no_commas (parser, NULL).value;
		  if (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    goto array_desig_after_first;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  while (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      struct c_expr next;
		      c_parser_consume_token (parser);
		      next = c_parser_expr_no_commas (parser, NULL);
		      next = default_function_array_conversion (next);
		      rec = build_compound_expr (rec, next.value);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.value
		    = objc_build_message_expr (build_tree_list (rec, args));
		  mexpr.original_code = ERROR_MARK;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr);
		  return;
		}
	      c_parser_consume_token (parser);
	      first = c_parser_expr_no_commas (parser, NULL).value;
	    array_desig_after_first:
	      if (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  c_parser_consume_token (parser);
		  second = c_parser_expr_no_commas (parser, NULL).value;
		}
	      else
		second = NULL_TREE;
	      if (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (first, second);
		  if (pedantic && second)
		    pedwarn ("ISO C forbids specifying range of "
			     "elements to initialize");
		}
	      else
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      if (des_seen >= 1)
	{
	  if (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      if (pedantic && !flag_isoc99)
		pedwarn ("ISO C90 forbids specifying subobject to initialize");
	      c_parser_consume_token (parser);
	    }
	  else
	    {
	      if (des_seen == 1)
		{
		  if (pedantic)
		    pedwarn ("obsolete use of designated initializer "
			     "without %<=%>");
		}
	      else
		{
		  struct c_expr init;
		  init.value = error_mark_node;
		  init.original_code = ERROR_MARK;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, NULL);
		  process_init_element (init);
		  return;
		}
	    }
	}
    }
  c_parser_initval (parser, NULL);
}