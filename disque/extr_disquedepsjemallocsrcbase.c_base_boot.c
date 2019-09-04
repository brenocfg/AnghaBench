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
 int /*<<< orphan*/  base_avail_szad ; 
 int /*<<< orphan*/  base_mtx ; 
 int /*<<< orphan*/ * base_nodes ; 
 int /*<<< orphan*/  extent_tree_szad_new (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *) ; 

bool
base_boot(void)
{

	if (malloc_mutex_init(&base_mtx))
		return (true);
	extent_tree_szad_new(&base_avail_szad);
	base_nodes = NULL;

	return (false);
}