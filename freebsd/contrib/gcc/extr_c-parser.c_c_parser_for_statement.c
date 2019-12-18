#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_11__ {scalar_t__ value; } ;
struct TYPE_10__ {scalar_t__ value; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int /*<<< orphan*/  location; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ keyword; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_KEYWORD ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ EXPR_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RID_EXTENSION ; 
 scalar_t__ RID_FOR ; 
 scalar_t__ RID_IN ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ build_tree_list (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ c_begin_compound_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ c_break_label ; 
 scalar_t__ c_cont_label ; 
 int /*<<< orphan*/  c_end_compound_stmt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_finish_expr_stmt (scalar_t__) ; 
 int /*<<< orphan*/  c_finish_loop (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ c_objc_common_truthvalue_conversion (scalar_t__) ; 
 scalar_t__ c_parser_attributes (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_c99_block_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_declaration_or_fndef (int /*<<< orphan*/ *,int,int,int,int,scalar_t__*) ; 
 TYPE_6__ c_parser_expression (int /*<<< orphan*/ *) ; 
 TYPE_5__ c_parser_expression_conv (int /*<<< orphan*/ *) ; 
 TYPE_4__ c_parser_initializer (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ c_parser_next_token_starts_declspecs (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 TYPE_2__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ c_process_expr_stmt (scalar_t__) ; 
 scalar_t__ c_token_starts_declspecs (TYPE_1__*) ; 
 int /*<<< orphan*/  check_for_loop_decls () ; 
 int disable_extension_diagnostics () ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ finish_parse_foreach_header (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ objc_foreach_context ; 
 int /*<<< orphan*/  restore_extension_diagnostics (int) ; 

__attribute__((used)) static void
c_parser_for_statement (c_parser *parser)
{
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  tree block, cond, incr, save_break, save_cont, body, attrs;
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  location_t loc;
  /* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
  bool foreach_p = false;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  attrs = c_parser_attributes (parser);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  block = c_begin_compound_stmt (flag_isoc99);
  if (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      /* Parse the initialization declaration or expression.  */
      if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  c_parser_consume_token (parser);
	  c_finish_expr_stmt (NULL_TREE);
	}
      else if (c_parser_next_token_starts_declspecs (parser))
	{
	  /* APPLE LOCAL begin radar 4708210 (for_objc_collection in 4.2) */
	  cond = NULL_TREE;
	  c_parser_declaration_or_fndef (parser, true, true, true, true, &cond);
	  /* APPLE LOCAL radar 5925639 */
	  if (c_parser_next_token_is_keyword (parser, RID_IN) && cond)
	    {
	      cond = finish_parse_foreach_header (parser, cond);
	      foreach_p = true;
	    }
	  else
	    check_for_loop_decls ();
	  /* APPLE LOCAL end radar 4708210 (for_objc_collection in 4.2) */
	}
      else if (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  while (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  if (c_token_starts_declspecs (c_parser_peek_2nd_token (parser)))
	    {
	      int ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      /* APPLE LOCAL begin radar 4708210 (for_objc_collection in 4.2) */
	      cond = NULL_TREE;
	      c_parser_declaration_or_fndef (parser, true, true, true, true, &cond);
	      restore_extension_diagnostics (ext);
	      /* APPLE LOCAL radar 5925639 */
	      if (c_parser_next_token_is_keyword (parser, RID_IN) && cond)
	        {
		  cond = finish_parse_foreach_header (parser, cond);
	          foreach_p = true;
	        }
	      else
		check_for_loop_decls ();
	      /* APPLE LOCAL end radar 4708210 (for_objc_collection in 4.2) */
	    }
	  else
	    goto init_expr;
	}
      else
	{
	init_expr:
	  /* APPLE LOCAL begin radar 4708210 (for_objc_collection in 4.2) */
	  cond = c_parser_expression (parser).value;
	  if (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser); /* IN */
	      cond = build_tree_list (cond, c_parser_initializer (parser).value); 
	      foreach_p = true;
	    }
	  else
	    {
	      c_finish_expr_stmt (cond);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	    }
	}
	objc_foreach_context = 0;
	/* APPLE LOCAL end radar 4708210 (for_objc_collection in 4.2) */
      /* Parse the loop condition.  */
      loc = c_parser_peek_token (parser)->location;
      if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  c_parser_consume_token (parser);
	  cond = NULL_TREE;
	}
      /* APPLE LOCAL begin radar 4708210 (for_objc_collection in 4.2) */
      else if (foreach_p)
	;
      /* APPLE LOCAL end radar 4708210 (for_objc_collection in 4.2) */
      else
	{
	  tree ocond = c_parser_expression_conv (parser).value;
	  cond = c_objc_common_truthvalue_conversion (ocond);
	  if (EXPR_P (cond))
	    SET_EXPR_LOCATION (cond, loc);
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      /* Parse the increment expression.  */
      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	incr = c_process_expr_stmt (NULL_TREE);
      else
	incr = c_process_expr_stmt (c_parser_expression (parser).value);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
    }
  else
    {
      cond = error_mark_node;
      incr = error_mark_node;
    }
  save_break = c_break_label;
  c_break_label = NULL_TREE;
  save_cont = c_cont_label;
  c_cont_label = NULL_TREE;
  body = c_parser_c99_block_statement (parser);
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
    c_finish_loop (loc, cond, incr, body, c_break_label, c_cont_label, attrs,
		   true);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  add_stmt (c_end_compound_stmt (block, flag_isoc99));
  c_break_label = save_break;
  c_cont_label = save_cont;
}