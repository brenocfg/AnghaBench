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
typedef  char* tree ;

/* Variables and functions */
 int /*<<< orphan*/  DERIVED_FROM_P (char*,char*) ; 
 char* TREE_OPERAND (char*,int /*<<< orphan*/ ) ; 
 char* TREE_TYPE (char*) ; 
 char* TYPE_MAIN_VARIANT (char*) ; 
 char* adjust_result_of_qualified_name_lookup (char*,char*,char*) ; 
 int /*<<< orphan*/  check_dtor_name (char*,char*) ; 
 int /*<<< orphan*/  complete_dtor_identifier ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 char* error_mark_node ; 
 char* lookup_member (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static tree
lookup_destructor (tree object, tree scope, tree dtor_name)
{
  tree object_type = TREE_TYPE (object);
  tree dtor_type = TREE_OPERAND (dtor_name, 0);
  tree expr;

  if (scope && !check_dtor_name (scope, dtor_type))
    {
      error ("qualified type %qT does not match destructor name ~%qT",
	     scope, dtor_type);
      return error_mark_node;
    }
  if (!DERIVED_FROM_P (dtor_type, TYPE_MAIN_VARIANT (object_type)))
    {
      error ("the type being destroyed is %qT, but the destructor refers to %qT",
	     TYPE_MAIN_VARIANT (object_type), dtor_type);
      return error_mark_node;
    }
  expr = lookup_member (dtor_type, complete_dtor_identifier,
			/*protect=*/1, /*want_type=*/false);
  expr = (adjust_result_of_qualified_name_lookup
	  (expr, dtor_type, object_type));
  return expr;
}