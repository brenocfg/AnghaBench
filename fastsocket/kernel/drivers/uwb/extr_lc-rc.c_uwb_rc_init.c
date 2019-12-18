#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * class; } ;
struct uwb_dev {TYPE_1__ dev; } ;
struct uwb_rc {int beaconing; TYPE_3__ uwb_beca; TYPE_2__ notifs_chain; int /*<<< orphan*/  scan_type; struct uwb_dev uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UWB_SCAN_DISABLED ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_dev_init (struct uwb_dev*) ; 
 int /*<<< orphan*/  uwb_drp_avail_init (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_class ; 
 int /*<<< orphan*/  uwb_rc_ie_init (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_neh_create (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_pal_init (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_sys_release ; 
 int /*<<< orphan*/  uwb_rsv_init (struct uwb_rc*) ; 

void uwb_rc_init(struct uwb_rc *rc)
{
	struct uwb_dev *uwb_dev = &rc->uwb_dev;

	uwb_dev_init(uwb_dev);
	rc->uwb_dev.dev.class = &uwb_rc_class;
	rc->uwb_dev.dev.release = uwb_rc_sys_release;
	uwb_rc_neh_create(rc);
	rc->beaconing = -1;
	rc->scan_type = UWB_SCAN_DISABLED;
	INIT_LIST_HEAD(&rc->notifs_chain.list);
	mutex_init(&rc->notifs_chain.mutex);
	INIT_LIST_HEAD(&rc->uwb_beca.list);
	mutex_init(&rc->uwb_beca.mutex);
	uwb_drp_avail_init(rc);
	uwb_rc_ie_init(rc);
	uwb_rsv_init(rc);
	uwb_rc_pal_init(rc);
}