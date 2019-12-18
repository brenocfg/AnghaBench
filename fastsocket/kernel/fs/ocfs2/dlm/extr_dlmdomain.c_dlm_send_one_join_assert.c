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
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  node_num; } ;
struct dlm_assert_joined {int /*<<< orphan*/  name_len; int /*<<< orphan*/  domain; int /*<<< orphan*/  node_idx; } ;
typedef  int /*<<< orphan*/  assert_msg ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_ASSERT_JOINED_MSG ; 
 int /*<<< orphan*/  DLM_MOD_KEY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_assert_joined*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_assert_joined*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_send_one_join_assert(struct dlm_ctxt *dlm,
				    unsigned int node)
{
	int status;
	struct dlm_assert_joined assert_msg;

	mlog(0, "Sending join assert to node %u\n", node);

	memset(&assert_msg, 0, sizeof(assert_msg));
	assert_msg.node_idx = dlm->node_num;
	assert_msg.name_len = strlen(dlm->name);
	memcpy(assert_msg.domain, dlm->name, assert_msg.name_len);

	status = o2net_send_message(DLM_ASSERT_JOINED_MSG, DLM_MOD_KEY,
				    &assert_msg, sizeof(assert_msg), node,
				    NULL);
	if (status < 0)
		mlog_errno(status);

	return status;
}