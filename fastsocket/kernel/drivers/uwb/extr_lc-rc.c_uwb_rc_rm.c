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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct uwb_rc {int /*<<< orphan*/  uwb_dev; TYPE_1__ uwb_beca; int /*<<< orphan*/ * cmd; int /*<<< orphan*/ * priv; int /*<<< orphan*/  (* stop ) (struct uwb_rc*) ;scalar_t__ ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  __uwb_rc_sys_rm (struct uwb_rc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_beca_release (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_dbg_del_rc (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_dev_for_each (struct uwb_rc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_offair_helper ; 
 int /*<<< orphan*/  uwb_dev_rm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_radio_shutdown (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_neh_destroy (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rsv_cleanup (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rsv_remove_all (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwbd_stop (struct uwb_rc*) ; 

void uwb_rc_rm(struct uwb_rc *rc)
{
	rc->ready = 0;

	uwb_dbg_del_rc(rc);
	uwb_rsv_remove_all(rc);
	uwb_radio_shutdown(rc);

	rc->stop(rc);

	uwbd_stop(rc);
	uwb_rc_neh_destroy(rc);

	uwb_dev_lock(&rc->uwb_dev);
	rc->priv = NULL;
	rc->cmd = NULL;
	uwb_dev_unlock(&rc->uwb_dev);
	mutex_lock(&rc->uwb_beca.mutex);
	uwb_dev_for_each(rc, uwb_dev_offair_helper, NULL);
	__uwb_rc_sys_rm(rc);
	mutex_unlock(&rc->uwb_beca.mutex);
	uwb_rsv_cleanup(rc);
 	uwb_beca_release(rc);
	uwb_dev_rm(&rc->uwb_dev);
}