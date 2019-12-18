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
typedef  int /*<<< orphan*/  uint32_t ;
struct rr_remote_endpoint {int /*<<< orphan*/  list; int /*<<< orphan*/  quota_lock; int /*<<< orphan*/  quota_wait; int /*<<< orphan*/  pid; int /*<<< orphan*/  cid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RPCROUTER_PID_REMOTE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct rr_remote_endpoint* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rr_remote_endpoint*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remote_endpoints ; 
 int /*<<< orphan*/  remote_endpoints_lock ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rpcrouter_create_remote_endpoint(uint32_t cid)
{
	struct rr_remote_endpoint *new_c;
	unsigned long flags;

	new_c = kmalloc(sizeof(struct rr_remote_endpoint), GFP_KERNEL);
	if (!new_c)
		return -ENOMEM;
	memset(new_c, 0, sizeof(struct rr_remote_endpoint));

	new_c->cid = cid;
	new_c->pid = RPCROUTER_PID_REMOTE;
	init_waitqueue_head(&new_c->quota_wait);
	spin_lock_init(&new_c->quota_lock);

	spin_lock_irqsave(&remote_endpoints_lock, flags);
	list_add_tail(&new_c->list, &remote_endpoints);
	spin_unlock_irqrestore(&remote_endpoints_lock, flags);
	return 0;
}