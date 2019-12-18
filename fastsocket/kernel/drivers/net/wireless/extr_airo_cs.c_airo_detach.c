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
struct pcmcia_device {scalar_t__ priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * eth_dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  airo_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  stop_airo_card (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void airo_detach(struct pcmcia_device *link)
{
	DEBUG(0, "airo_detach(0x%p)\n", link);

	airo_release(link);

	if (((local_info_t *)link->priv)->eth_dev) {
		stop_airo_card(((local_info_t *)link->priv)->eth_dev, 0);
	}
	((local_info_t *)link->priv)->eth_dev = NULL;

	kfree(link->priv);
}