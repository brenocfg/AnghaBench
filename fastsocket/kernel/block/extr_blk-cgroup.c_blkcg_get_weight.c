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
struct TYPE_2__ {unsigned int weight; } ;
struct blkio_policy_node {TYPE_1__ val; } ;
struct blkio_cgroup {unsigned int weight; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIO_POLICY_PROP ; 
 int /*<<< orphan*/  BLKIO_PROP_weight_device ; 
 struct blkio_policy_node* blkio_policy_search_node (struct blkio_cgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int blkcg_get_weight(struct blkio_cgroup *blkcg,
			      dev_t dev)
{
	struct blkio_policy_node *pn;

	pn = blkio_policy_search_node(blkcg, dev, BLKIO_POLICY_PROP,
				BLKIO_PROP_weight_device);
	if (pn)
		return pn->val.weight;
	else
		return blkcg->weight;
}