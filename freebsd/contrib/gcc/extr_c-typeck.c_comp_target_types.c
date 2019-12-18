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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ BLOCK_POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int comptypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int types_are_block_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comp_target_types (tree ttl, tree ttr)
{
  int val;
  tree mvl, mvr;

  /* APPLE LOCAL begin blocks 6065211 */
  if (TREE_CODE (ttl) == BLOCK_POINTER_TYPE
      && TREE_CODE (ttr) == BLOCK_POINTER_TYPE)
    return types_are_block_compatible (TREE_TYPE (ttl),
		       TREE_TYPE (ttr));
  if (TREE_CODE (ttl) != TREE_CODE (ttr))
    return 0;
  /* APPLE LOCAL end blocks 6065211 */

  /* Do not lose qualifiers on element types of array types that are
     pointer targets by taking their TYPE_MAIN_VARIANT.  */
  mvl = TREE_TYPE (ttl);
  mvr = TREE_TYPE (ttr);
  if (TREE_CODE (mvl) != ARRAY_TYPE)
    mvl = TYPE_MAIN_VARIANT (mvl);
  if (TREE_CODE (mvr) != ARRAY_TYPE)
    mvr = TYPE_MAIN_VARIANT (mvr);
  val = comptypes (mvl, mvr);

  if (val == 2 && pedantic)
    pedwarn ("types are not quite compatible");
  return val;
}