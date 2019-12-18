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
struct gcov_node {TYPE_1__* info; int /*<<< orphan*/  ghost; } ;
struct TYPE_2__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  gcov_info_dup (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ghost_node(struct gcov_node *node)
{
	node->ghost = gcov_info_dup(node->info);
	if (!node->ghost) {
		pr_warning("could not save data for '%s' (out of memory)\n",
			   node->info->filename);
		return -ENOMEM;
	}
	node->info = NULL;

	return 0;
}