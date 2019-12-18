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
struct urb {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*,scalar_t__) ; 

__attribute__((used)) static void ks959_speed_irq(struct urb *urb)
{
	/* unlink, shutdown, unplug, other nasties */
	if (urb->status != 0) {
		err("ks959_speed_irq: urb asynchronously failed - %d",
		    urb->status);
	}
}