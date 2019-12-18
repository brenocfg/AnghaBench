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
struct netfs_trans_dst {struct netfs_state* state; } ;
struct netfs_state {int /*<<< orphan*/  trans_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int netfs_trans_remove_nolock (struct netfs_trans_dst*,struct netfs_state*) ; 

__attribute__((used)) static int netfs_trans_remove_state(struct netfs_trans_dst *dst)
{
	int ret;
	struct netfs_state *st = dst->state;

	mutex_lock(&st->trans_lock);
	ret = netfs_trans_remove_nolock(dst, st);
	mutex_unlock(&st->trans_lock);

	return ret;
}