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
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_static_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_module_statics ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool 
has_proper_scope_for_analysis (tree t)
{
  /* If the variable has the "used" attribute, treat it as if it had a
     been touched by the devil.  */
  if (lookup_attribute ("used", DECL_ATTRIBUTES (t)))
    return false;

  /* Do not want to do anything with volatile except mark any
     function that uses one to be not const or pure.  */
  if (TREE_THIS_VOLATILE (t)) 
    return false;

  /* Do not care about a local automatic that is not static.  */
  if (!TREE_STATIC (t) && !DECL_EXTERNAL (t))
    return false;

  if (DECL_EXTERNAL (t) || TREE_PUBLIC (t))
    return false;

  /* This is a variable we care about.  Check if we have seen it
     before, and if not add it the set of variables we care about.  */
  if (!bitmap_bit_p (all_module_statics, DECL_UID (t)))
    add_static_var (t);

  return true;
}