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

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_WEAK (scalar_t__) ; 
 int /*<<< orphan*/  IDENTIFIER_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  OPT_Wpragmas ; 
 scalar_t__ SUPPORTS_WEAK ; 
 scalar_t__ TREE_SYMBOL_REFERENCED (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_USED (scalar_t__) ; 
 scalar_t__ build_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_tree_list (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  decl_attributes (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  declare_weak (scalar_t__) ; 
 int /*<<< orphan*/ * get_identifier (char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
apply_pragma_weak (tree decl, tree value)
{
  if (value)
    {
      value = build_string (IDENTIFIER_LENGTH (value),
			    IDENTIFIER_POINTER (value));
      decl_attributes (&decl, build_tree_list (get_identifier ("alias"),
					       build_tree_list (NULL, value)),
		       0);
    }

  if (SUPPORTS_WEAK && DECL_EXTERNAL (decl) && TREE_USED (decl)
      && !DECL_WEAK (decl) /* Don't complain about a redundant #pragma.  */
      && TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl)))
    warning (OPT_Wpragmas, "applying #pragma weak %q+D after first use "
	     "results in unspecified behavior", decl);

  declare_weak (decl);
}