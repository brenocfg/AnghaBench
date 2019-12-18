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
struct uwb_rc {int dummy; } ;
struct uwb_event {int /*<<< orphan*/  message; int /*<<< orphan*/  type; int /*<<< orphan*/  ts_jiffies; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  UWB_EVT_MSG_RESET ; 
 int /*<<< orphan*/  UWB_EVT_TYPE_MSG ; 
 int /*<<< orphan*/  __uwb_rc_get (struct uwb_rc*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct uwb_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwbd_event_queue (struct uwb_event*) ; 

void uwb_rc_reset_all(struct uwb_rc *rc)
{
	struct uwb_event *evt;

	evt = kzalloc(sizeof(struct uwb_event), GFP_ATOMIC);
	if (unlikely(evt == NULL))
		return;

	evt->rc = __uwb_rc_get(rc);	/* will be put by uwbd's uwbd_event_handle() */
	evt->ts_jiffies = jiffies;
	evt->type = UWB_EVT_TYPE_MSG;
	evt->message = UWB_EVT_MSG_RESET;

	uwbd_event_queue(evt);
}