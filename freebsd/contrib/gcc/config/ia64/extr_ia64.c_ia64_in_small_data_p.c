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
 scalar_t__ DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TARGET_NO_SDATA ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 char* TREE_STRING_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ ia64_section_threshold ; 
 scalar_t__ int_size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool
ia64_in_small_data_p (tree exp)
{
  if (TARGET_NO_SDATA)
    return false;

  /* We want to merge strings, so we never consider them small data.  */
  if (TREE_CODE (exp) == STRING_CST)
    return false;

  /* Functions are never small data.  */
  if (TREE_CODE (exp) == FUNCTION_DECL)
    return false;

  if (TREE_CODE (exp) == VAR_DECL && DECL_SECTION_NAME (exp))
    {
      const char *section = TREE_STRING_POINTER (DECL_SECTION_NAME (exp));

      if (strcmp (section, ".sdata") == 0
	  || strncmp (section, ".sdata.", 7) == 0
	  || strncmp (section, ".gnu.linkonce.s.", 16) == 0
	  || strcmp (section, ".sbss") == 0
	  || strncmp (section, ".sbss.", 6) == 0
	  || strncmp (section, ".gnu.linkonce.sb.", 17) == 0)
	return true;
    }
  else
    {
      HOST_WIDE_INT size = int_size_in_bytes (TREE_TYPE (exp));

      /* If this is an incomplete type with size 0, then we can't put it
	 in sdata because it might be too big when completed.  */
      if (size > 0 && size <= ia64_section_threshold)
	return true;
    }

  return false;
}