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
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
should_carry_locus_p (tree stmt)
{
  /* Don't emit a line note for a label.  We particularly don't want to
     emit one for the break label, since it doesn't actually correspond
     to the beginning of the loop/switch.  */
  if (TREE_CODE (stmt) == LABEL_EXPR)
    return false;

  /* Do not annotate empty statements, since it confuses gcov.  */
  if (!TREE_SIDE_EFFECTS (stmt))
    return false;

  return true;
}