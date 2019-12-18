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
struct usb_ov511 {scalar_t__ curframe; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ov51x_wait_frames_inactive(struct usb_ov511 *ov)
{
	return wait_event_interruptible(ov->wq, ov->curframe < 0);
}