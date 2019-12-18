#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int /*<<< orphan*/  priv; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ pcnet_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 TYPE_1__* PRIV (int /*<<< orphan*/ ) ; 
 int USE_SHMEM ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void pcnet_release(struct pcmcia_device *link)
{
	pcnet_dev_t *info = PRIV(link->priv);

	DEBUG(0, "pcnet_release(0x%p)\n", link);

	if (info->flags & USE_SHMEM)
		iounmap(info->base);

	pcmcia_disable_device(link);
}