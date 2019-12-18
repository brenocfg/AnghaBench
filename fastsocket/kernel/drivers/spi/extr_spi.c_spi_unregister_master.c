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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct spi_master {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister ; 
 int device_for_each_child (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 

void spi_unregister_master(struct spi_master *master)
{
	int dummy;

	dummy = device_for_each_child(master->dev.parent, &master->dev,
					__unregister);
	device_unregister(&master->dev);
}