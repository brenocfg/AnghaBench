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
struct usb_ov511 {int /*<<< orphan*/  buf_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov51x_do_dealloc (struct usb_ov511*) ; 

__attribute__((used)) static void
ov51x_dealloc(struct usb_ov511 *ov)
{
	PDEBUG(4, "entered");
	mutex_lock(&ov->buf_lock);
	ov51x_do_dealloc(ov);
	mutex_unlock(&ov->buf_lock);
	PDEBUG(4, "leaving");
}