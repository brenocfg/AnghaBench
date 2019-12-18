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
 int /*<<< orphan*/  gc ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shared_lookup_vuses ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/ * value_table ; 

void
vn_delete (void)
{
  htab_delete (value_table);
  VEC_free (tree, gc, shared_lookup_vuses);
  value_table = NULL;
}