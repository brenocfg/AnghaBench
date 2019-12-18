#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct capi_driver {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cardnr; int /*<<< orphan*/  irq; scalar_t__ port; } ;
typedef  TYPE_2__ capicardparams ;
struct TYPE_8__ {int /*<<< orphan*/  irq; TYPE_1__* resource; } ;
struct TYPE_6__ {scalar_t__ start; } ;

/* Variables and functions */
 int ENODEV ; 
 int MAX_CARDS ; 
 TYPE_3__* isa_dev ; 
 scalar_t__ t1isa_probe (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t1isa_add_card(struct capi_driver *driver, capicardparams *data)
{
	int i;

	for (i = 0; i < MAX_CARDS; i++) {
		if (isa_dev[i].resource[0].start)
			continue;

		isa_dev[i].resource[0].start = data->port;
		isa_dev[i].irq = data->irq;

		if (t1isa_probe(&isa_dev[i], data->cardnr) == 0)
			return 0;
	}
	return -ENODEV;
}