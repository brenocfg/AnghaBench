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
struct TYPE_2__ {int /*<<< orphan*/  (* global_decl ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 TYPE_1__* debug_hooks ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void
c_write_global_declarations_2 (tree globals)
{
  tree decl;

  for (decl = globals; decl ; decl = TREE_CHAIN (decl))
    debug_hooks->global_decl (decl);
}