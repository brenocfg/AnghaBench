#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {TYPE_2__* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  minor; } ;
struct TYPE_4__ {TYPE_1__ node; } ;
typedef  TYPE_2__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  HiSax_closecard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void avma1cs_release(struct pcmcia_device *link)
{
	local_info_t *local = link->priv;

	DEBUG(0, "avma1cs_release(0x%p)\n", link);

	/* now unregister function with hisax */
	HiSax_closecard(local->node.minor);

	pcmcia_disable_device(link);
}