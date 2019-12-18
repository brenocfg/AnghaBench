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
typedef  void* tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 void* NULL_TREE ; 
 int /*<<< orphan*/  RID_WHILE ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 void* c_begin_compound_stmt (int /*<<< orphan*/ ) ; 
 void* c_break_label ; 
 void* c_cont_label ; 
 int /*<<< orphan*/  c_end_compound_stmt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_finish_loop (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,void*,void*,void*,void*,int) ; 
 void* c_parser_attributes (int /*<<< orphan*/ *) ; 
 void* c_parser_c99_block_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* c_parser_paren_condition (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
c_parser_while_statement (c_parser *parser)
{
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  tree block, cond, body, save_break, save_cont, attrs;
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  c_parser_consume_token (parser);
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  attrs = c_parser_attributes (parser);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  save_break = c_break_label;
  c_break_label = NULL_TREE;
  save_cont = c_cont_label;
  c_cont_label = NULL_TREE;
  body = c_parser_c99_block_statement (parser);
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  c_finish_loop (loc, cond, NULL, body, c_break_label, c_cont_label, attrs,
		 true);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
  add_stmt (c_end_compound_stmt (block, flag_isoc99));
  c_break_label = save_break;
  c_cont_label = save_cont;
}