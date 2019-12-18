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
struct et131x_adapter {scalar_t__ MediaState; int /*<<< orphan*/  netdev; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 scalar_t__ NETIF_STATUS_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  fMP_ADAPTER_LINK_DETECTION ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void et131x_link_detection_handler(unsigned long data)
{
	struct et131x_adapter *etdev = (struct et131x_adapter *) data;
	unsigned long flags;

	if (etdev->MediaState == 0) {
		spin_lock_irqsave(&etdev->Lock, flags);

		etdev->MediaState = NETIF_STATUS_MEDIA_DISCONNECT;
		etdev->Flags &= ~fMP_ADAPTER_LINK_DETECTION;

		spin_unlock_irqrestore(&etdev->Lock, flags);

		netif_carrier_off(etdev->netdev);
	}
}