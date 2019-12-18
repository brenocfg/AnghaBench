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
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonical_type_variant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
canonicalize_for_substitution (tree node)
{
  /* For a TYPE_DECL, use the type instead.  */
  if (TREE_CODE (node) == TYPE_DECL)
    node = TREE_TYPE (node);
  if (TYPE_P (node))
    node = canonical_type_variant (node);

  return node;
}