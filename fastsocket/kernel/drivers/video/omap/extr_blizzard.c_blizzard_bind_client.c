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
struct omapfb_notifier_block {int dummy; } ;
struct TYPE_2__ {scalar_t__ update_mode; int /*<<< orphan*/  fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_EVENT_READY ; 
 scalar_t__ OMAPFB_MANUAL_UPDATE ; 
 TYPE_1__ blizzard ; 
 int /*<<< orphan*/  omapfb_notify_clients (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blizzard_bind_client(struct omapfb_notifier_block *nb)
{
	if (blizzard.update_mode == OMAPFB_MANUAL_UPDATE) {
		omapfb_notify_clients(blizzard.fbdev, OMAPFB_EVENT_READY);
	}
}