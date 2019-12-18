#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ using_directives; } ;

/* Variables and functions */
 scalar_t__ DECL_NAMESPACE_USING (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 TYPE_1__* current_binding_level ; 
 int /*<<< orphan*/  current_decl_namespace () ; 
 scalar_t__ namespace_ancestor (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ purpose_member (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
push_using_directive (tree used)
{
  tree ud = current_binding_level->using_directives;
  tree iter, ancestor;

  timevar_push (TV_NAME_LOOKUP);
  /* Check if we already have this.  */
  if (purpose_member (used, ud) != NULL_TREE)
    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, NULL_TREE);

  ancestor = namespace_ancestor (current_decl_namespace (), used);
  ud = current_binding_level->using_directives;
  ud = tree_cons (used, ancestor, ud);
  current_binding_level->using_directives = ud;

  /* Recursively add all namespaces used.  */
  for (iter = DECL_NAMESPACE_USING (used); iter; iter = TREE_CHAIN (iter))
    push_using_directive (TREE_PURPOSE (iter));

  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, ud);
}