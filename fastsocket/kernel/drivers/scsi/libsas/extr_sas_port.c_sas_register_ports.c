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
struct sas_ha_struct {int num_phys; struct asd_sas_port** sas_port; } ;
struct asd_sas_port {int /*<<< orphan*/  disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sas_init_disc (int /*<<< orphan*/ *,struct asd_sas_port*) ; 
 int /*<<< orphan*/  sas_init_port (struct asd_sas_port*,struct sas_ha_struct*,int) ; 

int sas_register_ports(struct sas_ha_struct *sas_ha)
{
	int i;

	/* initialize the ports and discovery */
	for (i = 0; i < sas_ha->num_phys; i++) {
		struct asd_sas_port *port = sas_ha->sas_port[i];

		sas_init_port(port, sas_ha, i);
		sas_init_disc(&port->disc, port);
	}
	return 0;
}