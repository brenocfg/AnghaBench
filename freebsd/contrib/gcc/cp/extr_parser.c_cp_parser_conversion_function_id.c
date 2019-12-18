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
struct TYPE_5__ {scalar_t__ scope; scalar_t__ qualifying_scope; scalar_t__ object_scope; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_OPERATOR ; 
 scalar_t__ cp_parser_conversion_type_id (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ mangle_conv_op_name_for_type (scalar_t__) ; 
 int /*<<< orphan*/  pop_scope (scalar_t__) ; 
 scalar_t__ push_scope (scalar_t__) ; 

__attribute__((used)) static tree
cp_parser_conversion_function_id (cp_parser* parser)
{
  tree type;
  tree saved_scope;
  tree saved_qualifying_scope;
  tree saved_object_scope;
  tree pushed_scope = NULL_TREE;

  /* Look for the `operator' token.  */
  if (!cp_parser_require_keyword (parser, RID_OPERATOR, "`operator'"))
    return error_mark_node;
  /* When we parse the conversion-type-id, the current scope will be
     reset.  However, we need that information in able to look up the
     conversion function later, so we save it here.  */
  saved_scope = parser->scope;
  saved_qualifying_scope = parser->qualifying_scope;
  saved_object_scope = parser->object_scope;
  /* We must enter the scope of the class so that the names of
     entities declared within the class are available in the
     conversion-type-id.  For example, consider:

       struct S {
	 typedef int I;
	 operator I();
       };

       S::operator I() { ... }

     In order to see that `I' is a type-name in the definition, we
     must be in the scope of `S'.  */
  if (saved_scope)
    pushed_scope = push_scope (saved_scope);
  /* Parse the conversion-type-id.  */
  type = cp_parser_conversion_type_id (parser);
  /* Leave the scope of the class, if any.  */
  if (pushed_scope)
    pop_scope (pushed_scope);
  /* Restore the saved scope.  */
  parser->scope = saved_scope;
  parser->qualifying_scope = saved_qualifying_scope;
  parser->object_scope = saved_object_scope;
  /* If the TYPE is invalid, indicate failure.  */
  if (type == error_mark_node)
    return error_mark_node;
  return mangle_conv_op_name_for_type (type);
}