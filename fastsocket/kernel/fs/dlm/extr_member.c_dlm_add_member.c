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
struct dlm_member {int nodeid; int weight; } ;
struct dlm_ls {int /*<<< orphan*/  ls_num_nodes; int /*<<< orphan*/  ls_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  add_ordered_member (struct dlm_ls*,struct dlm_member*) ; 
 int dlm_lowcomms_connect_node (int) ; 
 int dlm_node_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct dlm_member*) ; 
 struct dlm_member* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_add_member(struct dlm_ls *ls, int nodeid)
{
	struct dlm_member *memb;
	int w, error;

	memb = kzalloc(sizeof(struct dlm_member), GFP_NOFS);
	if (!memb)
		return -ENOMEM;

	w = dlm_node_weight(ls->ls_name, nodeid);
	if (w < 0) {
		kfree(memb);
		return w;
	}

	error = dlm_lowcomms_connect_node(nodeid);
	if (error < 0) {
		kfree(memb);
		return error;
	}

	memb->nodeid = nodeid;
	memb->weight = w;
	add_ordered_member(ls, memb);
	ls->ls_num_nodes++;
	return 0;
}