#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_mem_initializer_id (TYPE_1__*) ; 
 scalar_t__ cp_parser_parenthesized_expression_list (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ expand_member_init (scalar_t__) ; 
 int in_base_initializer ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static tree
cp_parser_mem_initializer (cp_parser* parser)
{
  tree mem_initializer_id;
  tree expression_list;
  tree member;

  /* Find out what is being initialized.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      pedwarn ("anachronistic old-style base class initializer");
      mem_initializer_id = NULL_TREE;
    }
  else
    mem_initializer_id = cp_parser_mem_initializer_id (parser);
  member = expand_member_init (mem_initializer_id);
  if (member && !DECL_P (member))
    in_base_initializer = 1;

  expression_list
    = cp_parser_parenthesized_expression_list (parser, false,
					       /*cast_p=*/false,
					       /*non_constant_p=*/NULL);
  if (expression_list == error_mark_node)
    return error_mark_node;
  if (!expression_list)
    expression_list = void_type_node;

  in_base_initializer = 0;

  return member ? build_tree_list (member, expression_list) : error_mark_node;
}