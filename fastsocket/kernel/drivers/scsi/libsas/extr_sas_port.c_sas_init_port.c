#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sas_ha_struct {int dummy; } ;
struct asd_sas_port {int id; int /*<<< orphan*/  dev_list_lock; struct sas_ha_struct* ha; int /*<<< orphan*/  phy_list; int /*<<< orphan*/  phy_list_lock; int /*<<< orphan*/  destroy_list; int /*<<< orphan*/  disco_list; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct asd_sas_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sas_init_port(struct asd_sas_port *port,
			  struct sas_ha_struct *sas_ha, int i)
{
	memset(port, 0, sizeof(*port));
	port->id = i;
	INIT_LIST_HEAD(&port->dev_list);
	INIT_LIST_HEAD(&port->disco_list);
	INIT_LIST_HEAD(&port->destroy_list);
	spin_lock_init(&port->phy_list_lock);
	INIT_LIST_HEAD(&port->phy_list);
	port->ha = sas_ha;

	spin_lock_init(&port->dev_list_lock);
}