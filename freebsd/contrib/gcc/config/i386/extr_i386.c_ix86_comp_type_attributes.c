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

/* Variables and functions */
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ TARGET_RTD ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ ix86_function_regparm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_attribute (char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ix86_comp_type_attributes (tree type1, tree type2)
{
  /* Check for mismatch of non-default calling convention.  */
  const char *const rtdstr = TARGET_RTD ? "cdecl" : "stdcall";

  if (TREE_CODE (type1) != FUNCTION_TYPE)
    return 1;

  /* Check for mismatched fastcall/regparm types.  */
  if ((!lookup_attribute ("fastcall", TYPE_ATTRIBUTES (type1))
       != !lookup_attribute ("fastcall", TYPE_ATTRIBUTES (type2)))
      || (ix86_function_regparm (type1, NULL)
	  != ix86_function_regparm (type2, NULL)))
    return 0;

  /* Check for mismatched sseregparm types.  */
  if (!lookup_attribute ("sseregparm", TYPE_ATTRIBUTES (type1))
      != !lookup_attribute ("sseregparm", TYPE_ATTRIBUTES (type2)))
    return 0;

  /* Check for mismatched return types (cdecl vs stdcall).  */
  if (!lookup_attribute (rtdstr, TYPE_ATTRIBUTES (type1))
      != !lookup_attribute (rtdstr, TYPE_ATTRIBUTES (type2)))
    return 0;

  return 1;
}