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
struct c_binding {int /*<<< orphan*/  decl; int /*<<< orphan*/  invisible; } ;

/* Variables and functions */
 struct c_binding* I_SYMBOL_BINDING (int /*<<< orphan*/ ) ; 

tree
lookup_name (tree name)
{
  struct c_binding *b = I_SYMBOL_BINDING (name);
  if (b && !b->invisible)
    return b->decl;
  return 0;
}