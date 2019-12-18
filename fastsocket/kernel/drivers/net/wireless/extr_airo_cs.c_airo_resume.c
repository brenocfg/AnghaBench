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
struct pcmcia_device {scalar_t__ open; TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  eth_dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_airo_card (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int airo_resume(struct pcmcia_device *link)
{
	local_info_t *local = link->priv;

	if (link->open) {
		reset_airo_card(local->eth_dev);
		netif_device_attach(local->eth_dev);
	}

	return 0;
}