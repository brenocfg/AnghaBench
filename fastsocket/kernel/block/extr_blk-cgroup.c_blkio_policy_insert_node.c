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
struct blkio_policy_node {int /*<<< orphan*/  node; } ;
struct blkio_cgroup {int /*<<< orphan*/  policy_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void blkio_policy_insert_node(struct blkio_cgroup *blkcg,
					    struct blkio_policy_node *pn)
{
	list_add(&pn->node, &blkcg->policy_list);
}