#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ next; TYPE_1__* dev; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_7__ {TYPE_2__* netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_4__* dev ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

isdn_net_dev *
isdn_net_findif(char *name)
{
	isdn_net_dev *p = dev->netdev;

	while (p) {
		if (!strcmp(p->dev->name, name))
			return p;
		p = (isdn_net_dev *) p->next;
	}
	return (isdn_net_dev *) NULL;
}