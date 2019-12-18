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
typedef  int /*<<< orphan*/  uint64_t ;
struct rds_sock {int /*<<< orphan*/  rs_lock; int /*<<< orphan*/  rs_cong_notify; } ;
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  notify ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_CMSG_CONG_UPDATE ; 
 int /*<<< orphan*/  SOL_RDS ; 
 int put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rds_notify_cong(struct rds_sock *rs, struct msghdr *msghdr)
{
	uint64_t notify = rs->rs_cong_notify;
	unsigned long flags;
	int err;

	err = put_cmsg(msghdr, SOL_RDS, RDS_CMSG_CONG_UPDATE,
			sizeof(notify), &notify);
	if (err)
		return err;

	spin_lock_irqsave(&rs->rs_lock, flags);
	rs->rs_cong_notify &= ~notify;
	spin_unlock_irqrestore(&rs->rs_lock, flags);

	return 0;
}