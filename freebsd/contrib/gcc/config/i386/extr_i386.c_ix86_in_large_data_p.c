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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CM_MEDIUM ; 
 scalar_t__ CM_MEDIUM_PIC ; 
 scalar_t__ DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 char* TREE_STRING_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ int_size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ ix86_cmodel ; 
 scalar_t__ ix86_section_threshold ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool
ix86_in_large_data_p (tree exp)
{
  if (ix86_cmodel != CM_MEDIUM && ix86_cmodel != CM_MEDIUM_PIC)
    return false;

  /* Functions are never large data.  */
  if (TREE_CODE (exp) == FUNCTION_DECL)
    return false;

  if (TREE_CODE (exp) == VAR_DECL && DECL_SECTION_NAME (exp))
    {
      const char *section = TREE_STRING_POINTER (DECL_SECTION_NAME (exp));
      if (strcmp (section, ".ldata") == 0
	  || strcmp (section, ".lbss") == 0)
	return true;
      return false;
    }
  else
    {
      HOST_WIDE_INT size = int_size_in_bytes (TREE_TYPE (exp));

      /* If this is an incomplete type with size 0, then we can't put it
	 in data because it might be too big when completed.  */
      if (!size || size > ix86_section_threshold)
	return true;
    }

  return false;
}