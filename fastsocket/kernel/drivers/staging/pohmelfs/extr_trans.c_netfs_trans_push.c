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
struct netfs_trans {int flags; int result; } ;
struct netfs_state {int /*<<< orphan*/  psb; } ;

/* Variables and functions */
 int NETFS_TRANS_SINGLE_DST ; 
 int /*<<< orphan*/  netfs_trans_drop_last (struct netfs_trans*,struct netfs_state*) ; 
 int netfs_trans_push_dst (struct netfs_trans*,struct netfs_state*) ; 
 int netfs_trans_send (struct netfs_trans*,struct netfs_state*) ; 
 int /*<<< orphan*/  pohmelfs_switch_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netfs_trans_push(struct netfs_trans *t, struct netfs_state *st)
{
	int err;

	err = netfs_trans_push_dst(t, st);
	if (err)
		return err;

	err = netfs_trans_send(t, st);
	if (err)
		goto err_out_free;

	if (t->flags & NETFS_TRANS_SINGLE_DST)
		pohmelfs_switch_active(st->psb);

	return 0;

err_out_free:
	t->result = err;
	netfs_trans_drop_last(t, st);

	return err;
}