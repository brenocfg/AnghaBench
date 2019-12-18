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
typedef  scalar_t__ uint32_t ;
struct rr_server {int pid; int /*<<< orphan*/  vers; int /*<<< orphan*/  prog; int /*<<< orphan*/  cid; } ;
struct msm_rpc_endpoint {int reply_pid; int dst_pid; int /*<<< orphan*/  list; int /*<<< orphan*/  incomplete; int /*<<< orphan*/  read_q_wake_lock; int /*<<< orphan*/  read_q_lock; int /*<<< orphan*/  read_q; int /*<<< orphan*/  wait_q; void* dst_vers; void* dst_prog; int /*<<< orphan*/  dst_cid; scalar_t__ dev; int /*<<< orphan*/  pid; scalar_t__ cid; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  D (char*,struct msm_rpc_endpoint*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCROUTER_PID_LOCAL ; 
 int /*<<< orphan*/  WAKE_LOCK_SUSPEND ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct msm_rpc_endpoint* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_endpoints ; 
 int /*<<< orphan*/  local_endpoints_lock ; 
 int /*<<< orphan*/  memset (struct msm_rpc_endpoint*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msm_rpcrouter_devno ; 
 struct rr_server* rpcrouter_lookup_server_by_dev (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

struct msm_rpc_endpoint *msm_rpcrouter_create_local_endpoint(dev_t dev)
{
	struct msm_rpc_endpoint *ept;
	unsigned long flags;

	ept = kmalloc(sizeof(struct msm_rpc_endpoint), GFP_KERNEL);
	if (!ept)
		return NULL;
	memset(ept, 0, sizeof(struct msm_rpc_endpoint));

	/* mark no reply outstanding */
	ept->reply_pid = 0xffffffff;

	ept->cid = (uint32_t) ept;
	ept->pid = RPCROUTER_PID_LOCAL;
	ept->dev = dev;

	if ((dev != msm_rpcrouter_devno) && (dev != MKDEV(0, 0))) {
		struct rr_server *srv;
		/*
		 * This is a userspace client which opened
		 * a program/ver devicenode. Bind the client
		 * to that destination
		 */
		srv = rpcrouter_lookup_server_by_dev(dev);
		/* TODO: bug? really? */
		BUG_ON(!srv);

		ept->dst_pid = srv->pid;
		ept->dst_cid = srv->cid;
		ept->dst_prog = cpu_to_be32(srv->prog);
		ept->dst_vers = cpu_to_be32(srv->vers);

		D("Creating local ept %p @ %08x:%08x\n", ept, srv->prog, srv->vers);
	} else {
		/* mark not connected */
		ept->dst_pid = 0xffffffff;
		D("Creating a master local ept %p\n", ept);
	}

	init_waitqueue_head(&ept->wait_q);
	INIT_LIST_HEAD(&ept->read_q);
	spin_lock_init(&ept->read_q_lock);
	wake_lock_init(&ept->read_q_wake_lock, WAKE_LOCK_SUSPEND, "rpc_read");
	INIT_LIST_HEAD(&ept->incomplete);

	spin_lock_irqsave(&local_endpoints_lock, flags);
	list_add_tail(&ept->list, &local_endpoints);
	spin_unlock_irqrestore(&local_endpoints_lock, flags);
	return ept;
}