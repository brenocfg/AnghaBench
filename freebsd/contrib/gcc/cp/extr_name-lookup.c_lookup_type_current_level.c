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
struct cp_binding_level {scalar_t__ kind; struct cp_binding_level* level_chain; int /*<<< orphan*/  type_shadowed; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ REAL_IDENTIFIER_TYPE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 struct cp_binding_level* current_binding_level ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ global_type_node ; 
 scalar_t__ purpose_member (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_cleanup ; 
 scalar_t__ sk_namespace ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
lookup_type_current_level (tree name)
{
  tree t = NULL_TREE;

  timevar_push (TV_NAME_LOOKUP);
  gcc_assert (current_binding_level->kind != sk_namespace);

  if (REAL_IDENTIFIER_TYPE_VALUE (name) != NULL_TREE
      && REAL_IDENTIFIER_TYPE_VALUE (name) != global_type_node)
    {
      struct cp_binding_level *b = current_binding_level;
      while (1)
	{
	  if (purpose_member (name, b->type_shadowed))
	    POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP,
				    REAL_IDENTIFIER_TYPE_VALUE (name));
	  if (b->kind == sk_cleanup)
	    b = b->level_chain;
	  else
	    break;
	}
    }

  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, t);
}