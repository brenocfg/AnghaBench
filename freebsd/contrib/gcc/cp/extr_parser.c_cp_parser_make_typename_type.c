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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_diagnose_invalid_type_name (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ make_typename_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tf_error ; 
 int /*<<< orphan*/  tf_none ; 
 int /*<<< orphan*/  typename_type ; 

__attribute__((used)) static tree
cp_parser_make_typename_type (cp_parser *parser, tree scope, tree id)
{
  tree result;
  if (TREE_CODE (id) == IDENTIFIER_NODE)
    {
      result = make_typename_type (scope, id, typename_type,
				   /*complain=*/tf_none);
      if (result == error_mark_node)
	cp_parser_diagnose_invalid_type_name (parser, scope, id);
      return result;
    }
  return make_typename_type (scope, id, typename_type, tf_error);
}