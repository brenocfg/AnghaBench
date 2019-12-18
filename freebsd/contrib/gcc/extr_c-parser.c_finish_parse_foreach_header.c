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
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 TYPE_1__ c_parser_initializer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_for_loop_decls () ; 
 int /*<<< orphan*/  finish_init () ; 
 int flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
finish_parse_foreach_header (c_parser *parser, tree foreach_elem_selector)
{
  tree res;
  int save_flag_isoc99 = flag_isoc99;
  gcc_assert (foreach_elem_selector);
  /* Consume 'in' keyword */
  c_parser_consume_token (parser); 
  res = build_tree_list (foreach_elem_selector, c_parser_initializer (parser).value); 
  finish_init ();
  flag_isoc99 = 1;
  check_for_loop_decls ();
  flag_isoc99 = save_flag_isoc99;
  return res;
}