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
 int AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DECL_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
use_pointer_in_frame (tree decl)
{
  if (TREE_CODE (decl) == PARM_DECL)
    {
      /* It's illegal to copy TREE_ADDRESSABLE, impossible to copy variable
         sized decls, and inefficient to copy large aggregates.  Don't bother
         moving anything but scalar variables.  */
      return AGGREGATE_TYPE_P (TREE_TYPE (decl));
    }
  else
    {
      /* Variable sized types make things "interesting" in the frame.  */
      return DECL_SIZE (decl) == NULL || !TREE_CONSTANT (DECL_SIZE (decl));
    }
}