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
struct pohmelfs_sb {int dummy; } ;
struct TYPE_2__ {struct netfs_cmd* iov_base; } ;
struct netfs_trans {int result; TYPE_1__ iovec; } ;
struct netfs_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netfs_convert_cmd (struct netfs_cmd*) ; 
 int netfs_trans_finish_send (struct netfs_trans*,struct pohmelfs_sb*) ; 
 int /*<<< orphan*/  netfs_trans_put (struct netfs_trans*) ; 

__attribute__((used)) static int pohmelfs_crypto_finish(struct netfs_trans *t, struct pohmelfs_sb *psb, int err)
{
	struct netfs_cmd *cmd = t->iovec.iov_base;
	netfs_convert_cmd(cmd);

	if (likely(!err))
		err = netfs_trans_finish_send(t, psb);

	t->result = err;
	netfs_trans_put(t);

	return err;
}