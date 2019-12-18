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
struct niu {int port; int num_ldg; int num_rx_rings; int num_tx_rings; TYPE_1__* dev; int /*<<< orphan*/ * irq_name; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static void niu_set_irq_name(struct niu *np)
{
	int port = np->port;
	int i, j = 1;

	sprintf(np->irq_name[0], "%s:MAC", np->dev->name);

	if (port == 0) {
		sprintf(np->irq_name[1], "%s:MIF", np->dev->name);
		sprintf(np->irq_name[2], "%s:SYSERR", np->dev->name);
		j = 3;
	}

	for (i = 0; i < np->num_ldg - j; i++) {
		if (i < np->num_rx_rings)
			sprintf(np->irq_name[i+j], "%s-rx-%d",
				np->dev->name, i);
		else if (i < np->num_tx_rings + np->num_rx_rings)
			sprintf(np->irq_name[i+j], "%s-tx-%d", np->dev->name,
				i - np->num_rx_rings);
	}
}