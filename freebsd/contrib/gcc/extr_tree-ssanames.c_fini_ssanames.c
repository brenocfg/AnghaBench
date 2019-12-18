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

/* Variables and functions */
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * free_ssanames ; 
 int /*<<< orphan*/  gc ; 
 int /*<<< orphan*/  ssa_names ; 
 int /*<<< orphan*/  tree ; 

void
fini_ssanames (void)
{
  VEC_free (tree, gc, ssa_names);
  free_ssanames = NULL;
}