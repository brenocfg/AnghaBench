#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  cxx_scope ;
struct TYPE_6__ {int /*<<< orphan*/ * previous; int /*<<< orphan*/ * scope; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 TYPE_1__* IDENTIFIER_NAMESPACE_BINDINGS (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_binding (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static inline cxx_binding *
cxx_scope_find_binding_for_name (cxx_scope *scope, tree name)
{
  cxx_binding *b = IDENTIFIER_NAMESPACE_BINDINGS (name);
  if (b)
    {
      /* Fold-in case where NAME is used only once.  */
      if (scope == b->scope && b->previous == NULL)
	return b;
      return find_binding (scope, b);
    }
  return NULL;
}