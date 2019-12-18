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
struct audmgr_disable_msg {int /*<<< orphan*/  handle; int /*<<< orphan*/  hdr; } ;
struct audmgr {scalar_t__ state; int /*<<< orphan*/  wait; int /*<<< orphan*/  ept; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  AUDMGR_DISABLE_CLIENT ; 
 int /*<<< orphan*/  AUDMGR_PROG ; 
 int /*<<< orphan*/  BUG () ; 
 int ENODEV ; 
 int HZ ; 
 scalar_t__ STATE_DISABLED ; 
 scalar_t__ STATE_DISABLING ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_rpc_get_vers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_rpc_setup_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msm_rpc_write (int /*<<< orphan*/ ,struct audmgr_disable_msg*,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

int audmgr_disable(struct audmgr *am)
{
	struct audmgr_disable_msg msg;
	int rc;

	if (am->state == STATE_DISABLED)
		return 0;

	msm_rpc_setup_req(&msg.hdr, AUDMGR_PROG, msm_rpc_get_vers(am->ept),
			  AUDMGR_DISABLE_CLIENT);
	msg.handle = cpu_to_be32(am->handle);

	am->state = STATE_DISABLING;

	rc = msm_rpc_write(am->ept, &msg, sizeof(msg));
	if (rc < 0)
		return rc;

	rc = wait_event_timeout(am->wait, am->state != STATE_DISABLING, 15 * HZ);
	if (rc == 0) {
		pr_err("audmgr_disable: ARM9 did not reply to RPC am->state = %d\n", am->state);
		BUG();
	}

	if (am->state == STATE_DISABLED)
		return 0;

	pr_err("audmgr: unexpected state %d while disabling?!\n", am->state);
	return -ENODEV;
}