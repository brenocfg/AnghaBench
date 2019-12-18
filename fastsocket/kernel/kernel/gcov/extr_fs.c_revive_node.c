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
struct gcov_node {struct gcov_info* info; int /*<<< orphan*/ * ghost; } ;
struct gcov_info {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_add (struct gcov_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcov_info_free (int /*<<< orphan*/ *) ; 
 scalar_t__ gcov_info_is_compatible (int /*<<< orphan*/ *,struct gcov_info*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void revive_node(struct gcov_node *node, struct gcov_info *info)
{
	if (gcov_info_is_compatible(node->ghost, info))
		gcov_info_add(info, node->ghost);
	else {
		pr_warning("discarding saved data for '%s' (version changed)\n",
			   info->filename);
	}
	gcov_info_free(node->ghost);
	node->ghost = NULL;
	node->info = info;
}