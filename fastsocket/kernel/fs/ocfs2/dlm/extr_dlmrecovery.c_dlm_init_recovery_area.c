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
typedef  int u8 ;
struct dlm_reco_node_data {int node_num; int /*<<< orphan*/  list; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  node_data; int /*<<< orphan*/  node_map; } ;
struct dlm_ctxt {TYPE_1__ reco; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_RECO_NODE_DATA_INIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  dlm_destroy_recovery_area (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  dlm_reco_state_lock ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 struct dlm_reco_node_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_init_recovery_area(struct dlm_ctxt *dlm, u8 dead_node)
{
	int num=0;
	struct dlm_reco_node_data *ndata;

	spin_lock(&dlm->spinlock);
	memcpy(dlm->reco.node_map, dlm->domain_map, sizeof(dlm->domain_map));
	/* nodes can only be removed (by dying) after dropping
	 * this lock, and death will be trapped later, so this should do */
	spin_unlock(&dlm->spinlock);

	while (1) {
		num = find_next_bit (dlm->reco.node_map, O2NM_MAX_NODES, num);
		if (num >= O2NM_MAX_NODES) {
			break;
		}
		BUG_ON(num == dead_node);

		ndata = kzalloc(sizeof(*ndata), GFP_NOFS);
		if (!ndata) {
			dlm_destroy_recovery_area(dlm, dead_node);
			return -ENOMEM;
		}
		ndata->node_num = num;
		ndata->state = DLM_RECO_NODE_DATA_INIT;
		spin_lock(&dlm_reco_state_lock);
		list_add_tail(&ndata->list, &dlm->reco.node_data);
		spin_unlock(&dlm_reco_state_lock);
		num++;
	}

	return 0;
}