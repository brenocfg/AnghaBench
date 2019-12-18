#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  c_parser_omp_variable_list (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static tree
c_parser_omp_var_list_parens (c_parser *parser, enum tree_code kind, tree list)
{
  if (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      list = c_parser_omp_variable_list (parser, kind, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
    }
  return list;
}