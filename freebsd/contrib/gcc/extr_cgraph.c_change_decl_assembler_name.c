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
 scalar_t__ DECL_ASSEMBLER_NAME (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME_SET_P (scalar_t__) ; 
 scalar_t__ DECL_RTL_SET_P (scalar_t__) ; 
 int /*<<< orphan*/  SET_DECL_ASSEMBLER_NAME (scalar_t__,scalar_t__) ; 
 scalar_t__ TREE_SYMBOL_REFERENCED (scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
change_decl_assembler_name (tree decl, tree name)
{
  if (!DECL_ASSEMBLER_NAME_SET_P (decl))
    {
      SET_DECL_ASSEMBLER_NAME (decl, name);
      return;
    }
  if (name == DECL_ASSEMBLER_NAME (decl))
    return;

  if (TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl))
      && DECL_RTL_SET_P (decl))
    warning (0, "%D renamed after being referenced in assembly", decl);

  SET_DECL_ASSEMBLER_NAME (decl, name);
}