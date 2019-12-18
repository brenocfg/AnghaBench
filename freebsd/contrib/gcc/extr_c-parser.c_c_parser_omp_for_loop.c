#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_12__ {int /*<<< orphan*/ * value; } ;
struct TYPE_11__ {int /*<<< orphan*/ * value; } ;
struct TYPE_10__ {int /*<<< orphan*/ * value; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  location; } ;
struct TYPE_7__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_EQ ; 
 int /*<<< orphan*/  CPP_NAME ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ EXPR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 void* NULL_TREE ; 
 int /*<<< orphan*/  RID_FOR ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_modify_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_break_label ; 
 int /*<<< orphan*/ * c_cont_label ; 
 int /*<<< orphan*/ * c_finish_omp_for (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_objc_common_truthvalue_conversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_c99_block_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_declaration_or_fndef (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 TYPE_6__ c_parser_expr_no_commas (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__ c_parser_expression (int /*<<< orphan*/ *) ; 
 TYPE_4__ c_parser_expression_conv (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_starts_declspecs (int /*<<< orphan*/ *) ; 
 TYPE_3__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 TYPE_2__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 TYPE_1__ c_parser_postfix_expression (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * c_process_expr_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * check_for_loop_decls () ; 
 int /*<<< orphan*/ * error_mark_node ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/ * pop_stmt_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * push_stmt_list () ; 
 int /*<<< orphan*/ * size_one_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
c_parser_omp_for_loop (c_parser *parser)
{
  tree decl, cond, incr, save_break, save_cont, body, init;
  location_t loc;

  if (!c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      c_parser_error (parser, "for statement expected");
      return NULL;
    }
  loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    return NULL;

  /* Parse the initialization declaration or expression.  */
  if (c_parser_next_token_starts_declspecs (parser))
    {
      /* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
      c_parser_declaration_or_fndef (parser, true, true, true, true, NULL);
      decl = check_for_loop_decls ();
      if (decl == NULL)
	goto error_init;
      init = decl;
    }
  else if (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      decl = c_parser_postfix_expression (parser).value;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init = c_parser_expr_no_commas (parser, NULL).value;
      init = build_modify_expr (decl, NOP_EXPR, init);
      init = c_process_expr_stmt (init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  else
    goto error_init;

  /* Parse the loop condition.  */
  cond = NULL_TREE;
  if (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      cond = c_parser_expression_conv (parser).value;
      cond = c_objc_common_truthvalue_conversion (cond);
      if (EXPR_P (cond))
	SET_EXPR_LOCATION (cond, input_location);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  incr = NULL_TREE;
  if (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    incr = c_process_expr_stmt (c_parser_expression (parser).value);
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");

 parse_body:
  save_break = c_break_label;
  c_break_label = size_one_node;
  save_cont = c_cont_label;
  c_cont_label = NULL_TREE;
  body = push_stmt_list ();

  add_stmt (c_parser_c99_block_statement (parser));
  if (c_cont_label)
    add_stmt (build1 (LABEL_EXPR, void_type_node, c_cont_label));

  body = pop_stmt_list (body);
  c_break_label = save_break;
  c_cont_label = save_cont;

  /* Only bother calling c_finish_omp_for if we havn't already generated
     an error from the initialization parsing.  */
  if (decl != NULL && decl != error_mark_node && init != error_mark_node)
    return c_finish_omp_for (loc, decl, init, cond, incr, body, NULL);
  return NULL;

 error_init:
  c_parser_error (parser, "expected iteration declaration or initialization");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
  decl = init = cond = incr = NULL_TREE;
  goto parse_body;
}