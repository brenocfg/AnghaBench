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
 scalar_t__ CONST_DECL ; 
 int /*<<< orphan*/  DECL_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
use_blocks_for_decl_p (tree decl)
{
  /* Only data DECLs can be placed into object blocks.  */
  if (TREE_CODE (decl) != VAR_DECL && TREE_CODE (decl) != CONST_DECL)
    return false;

  /* Detect decls created by dw2_force_const_mem.  Such decls are
     special because DECL_INITIAL doesn't specify the decl's true value.
     dw2_output_indirect_constants will instead call assemble_variable
     with dont_output_data set to 1 and then print the contents itself.  */
  if (DECL_INITIAL (decl) == decl)
    return false;

  /* If this decl is an alias, then we don't want to emit a definition.  */
  if (lookup_attribute ("alias", DECL_ATTRIBUTES (decl)))
    return false;

  return true;
}