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
 int /*<<< orphan*/  instantiate_decl (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mark_decl_instantiated (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
instantiate_class_member (tree decl, int extern_p)
{
  mark_decl_instantiated (decl, extern_p);
  if (! extern_p)
    instantiate_decl (decl, /*defer_ok=*/1,
		      /*expl_inst_class_mem_p=*/true);
}