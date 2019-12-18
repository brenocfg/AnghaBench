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
struct uwb_rsv {scalar_t__ state; int /*<<< orphan*/  pal_node; struct uwb_dbg* pal_priv; } ;
struct uwb_dbg {int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 scalar_t__ UWB_RSV_STATE_NONE ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rsv_destroy (struct uwb_rsv*) ; 
 int /*<<< orphan*/  uwb_rsv_dump (char*,struct uwb_rsv*) ; 

__attribute__((used)) static void uwb_dbg_rsv_cb(struct uwb_rsv *rsv)
{
	struct uwb_dbg *dbg = rsv->pal_priv;

	uwb_rsv_dump("debug", rsv);

	if (rsv->state == UWB_RSV_STATE_NONE) {
		spin_lock(&dbg->list_lock);
		list_del(&rsv->pal_node);
		spin_unlock(&dbg->list_lock);
		uwb_rsv_destroy(rsv);
	}
}