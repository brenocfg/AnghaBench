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
struct TYPE_4__ {int /*<<< orphan*/  AssignedIRQ; } ;
struct TYPE_3__ {int /*<<< orphan*/  BasePort1; } ;
struct pcmcia_device {TYPE_2__ irq; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  b1pcmcia_delcard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void avmcs_release(struct pcmcia_device *link)
{
	b1pcmcia_delcard(link->io.BasePort1, link->irq.AssignedIRQ);
	pcmcia_disable_device(link);
}