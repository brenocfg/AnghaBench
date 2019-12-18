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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct sas_port {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct sas_phy {TYPE_2__ dev; } ;

/* Variables and functions */
 char* dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void sas_port_delete_link(struct sas_port *port,
				 struct sas_phy *phy)
{
	sysfs_remove_link(&port->dev.kobj, dev_name(&phy->dev));
	sysfs_remove_link(&phy->dev.kobj, "port");
}