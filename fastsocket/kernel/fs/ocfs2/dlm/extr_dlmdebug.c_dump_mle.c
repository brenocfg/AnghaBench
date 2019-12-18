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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct dlm_master_list_entry {scalar_t__ type; int master; int new_master; int /*<<< orphan*/  node_map; int /*<<< orphan*/  response_map; int /*<<< orphan*/  vote_map; int /*<<< orphan*/  maybe_map; TYPE_1__ mle_refs; int /*<<< orphan*/  inuse; int /*<<< orphan*/  hb_events; int /*<<< orphan*/  mnamelen; int /*<<< orphan*/  mname; } ;

/* Variables and functions */
 scalar_t__ DLM_MLE_BLOCK ; 
 scalar_t__ DLM_MLE_MASTER ; 
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 scalar_t__ stringify_lockname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ stringify_nodemap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dump_mle(struct dlm_master_list_entry *mle, char *buf, int len)
{
	int out = 0;
	char *mle_type;

	if (mle->type == DLM_MLE_BLOCK)
		mle_type = "BLK";
	else if (mle->type == DLM_MLE_MASTER)
		mle_type = "MAS";
	else
		mle_type = "MIG";

	out += stringify_lockname(mle->mname, mle->mnamelen, buf + out, len - out);
	out += snprintf(buf + out, len - out,
			"\t%3s\tmas=%3u\tnew=%3u\tevt=%1d\tuse=%1d\tref=%3d\n",
			mle_type, mle->master, mle->new_master,
			!list_empty(&mle->hb_events),
			!!mle->inuse,
			atomic_read(&mle->mle_refs.refcount));

	out += snprintf(buf + out, len - out, "Maybe=");
	out += stringify_nodemap(mle->maybe_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += snprintf(buf + out, len - out, "\n");

	out += snprintf(buf + out, len - out, "Vote=");
	out += stringify_nodemap(mle->vote_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += snprintf(buf + out, len - out, "\n");

	out += snprintf(buf + out, len - out, "Response=");
	out += stringify_nodemap(mle->response_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += snprintf(buf + out, len - out, "\n");

	out += snprintf(buf + out, len - out, "Node=");
	out += stringify_nodemap(mle->node_map, O2NM_MAX_NODES,
				 buf + out, len - out);
	out += snprintf(buf + out, len - out, "\n");

	out += snprintf(buf + out, len - out, "\n");

	return out;
}