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
struct c_scope {int dummy; } ;
struct c_binding {int /*<<< orphan*/  decl; struct c_binding* shadowed; } ;

/* Variables and functions */
 scalar_t__ B_IN_SCOPE (struct c_binding*,struct c_scope*) ; 
 struct c_binding* I_SYMBOL_BINDING (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
lookup_name_in_scope (tree name, struct c_scope *scope)
{
  struct c_binding *b;

  for (b = I_SYMBOL_BINDING (name); b; b = b->shadowed)
    if (B_IN_SCOPE (b, scope))
      return b->decl;
  return 0;
}