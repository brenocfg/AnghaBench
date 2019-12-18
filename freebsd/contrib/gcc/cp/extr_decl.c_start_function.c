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
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_decl_specifier_seq ;

/* Variables and functions */
 scalar_t__ DECL_MAIN_P (scalar_t__) ; 
 int /*<<< orphan*/  FUNCDEF ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SF_DEFAULT ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  check_missing_prototype (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ grokdeclarator (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  same_type_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_preparsed_function (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int
start_function (cp_decl_specifier_seq *declspecs,
		const cp_declarator *declarator,
		tree attrs)
{
  tree decl1;

  decl1 = grokdeclarator (declarator, declspecs, FUNCDEF, 1, &attrs);
  /* If the declarator is not suitable for a function definition,
     cause a syntax error.  */
  if (decl1 == NULL_TREE || TREE_CODE (decl1) != FUNCTION_DECL)
    return 0;

  if (DECL_MAIN_P (decl1))
    /* main must return int.  grokfndecl should have corrected it
       (and issued a diagnostic) if the user got it wrong.  */
    gcc_assert (same_type_p (TREE_TYPE (TREE_TYPE (decl1)),
			     integer_type_node));

  /* APPLE LOCAL begin warn missing prototype 6261539 */
  check_missing_prototype (decl1);
  /* APPLE LOCAL end warn missing prototype 6261539 */

  start_preparsed_function (decl1, attrs, /*flags=*/SF_DEFAULT);

  return 1;
}