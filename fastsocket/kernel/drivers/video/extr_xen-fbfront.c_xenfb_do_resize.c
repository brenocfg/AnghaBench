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
union xenfb_out_event {int /*<<< orphan*/  resize; } ;
struct xenfb_info {int /*<<< orphan*/  resize; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union xenfb_out_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xenfb_send_event (struct xenfb_info*,union xenfb_out_event*) ; 

__attribute__((used)) static void xenfb_do_resize(struct xenfb_info *info)
{
	union xenfb_out_event event;

	memset(&event, 0, sizeof(event));
	event.resize = info->resize;

	/* caller ensures !xenfb_queue_full() */
	xenfb_send_event(info, &event);
}