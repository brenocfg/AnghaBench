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
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TARGET_ABICALLS ; 
 scalar_t__ TARGET_EMBEDDED_DATA ; 
 scalar_t__ TARGET_EXPLICIT_RELOCS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 char* TREE_STRING_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ int_size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ mips_section_threshold ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool
mips_in_small_data_p (tree decl)
{
  HOST_WIDE_INT size;

  if (TREE_CODE (decl) == STRING_CST || TREE_CODE (decl) == FUNCTION_DECL)
    return false;

  /* We don't yet generate small-data references for -mabicalls.  See related
     -G handling in override_options.  */
  if (TARGET_ABICALLS)
    return false;

  if (TREE_CODE (decl) == VAR_DECL && DECL_SECTION_NAME (decl) != 0)
    {
      const char *name;

      /* Reject anything that isn't in a known small-data section.  */
      name = TREE_STRING_POINTER (DECL_SECTION_NAME (decl));
      if (strcmp (name, ".sdata") != 0 && strcmp (name, ".sbss") != 0)
	return false;

      /* If a symbol is defined externally, the assembler will use the
	 usual -G rules when deciding how to implement macros.  */
      if (TARGET_EXPLICIT_RELOCS || !DECL_EXTERNAL (decl))
	return true;
    }
  else if (TARGET_EMBEDDED_DATA)
    {
      /* Don't put constants into the small data section: we want them
	 to be in ROM rather than RAM.  */
      if (TREE_CODE (decl) != VAR_DECL)
	return false;

      if (TREE_READONLY (decl)
	  && !TREE_SIDE_EFFECTS (decl)
	  && (!DECL_INITIAL (decl) || TREE_CONSTANT (DECL_INITIAL (decl))))
	return false;
    }

  size = int_size_in_bytes (TREE_TYPE (decl));
  return (size > 0 && size <= mips_section_threshold);
}