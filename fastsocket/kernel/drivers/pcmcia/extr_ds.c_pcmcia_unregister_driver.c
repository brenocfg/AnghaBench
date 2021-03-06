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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct pcmcia_driver {TYPE_1__ drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  ds_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_free_dynids (struct pcmcia_driver*) ; 

void pcmcia_unregister_driver(struct pcmcia_driver *driver)
{
	ds_dbg(3, "unregistering driver %s\n", driver->drv.name);
	driver_unregister(&driver->drv);
	pcmcia_free_dynids(driver);
}