#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sas_rphy {int /*<<< orphan*/  scsi_target_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct sas_port {int port_identifier; TYPE_1__ dev; int /*<<< orphan*/  phy_list; int /*<<< orphan*/  phy_list_mutex; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,int,...) ; 
 struct sas_rphy* dev_to_rphy (struct device*) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 struct sas_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_port_release ; 
 scalar_t__ scsi_is_sas_expander_device (struct device*) ; 
 int /*<<< orphan*/  transport_setup_device (TYPE_1__*) ; 

struct sas_port *sas_port_alloc(struct device *parent, int port_id)
{
	struct Scsi_Host *shost = dev_to_shost(parent);
	struct sas_port *port;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port)
		return NULL;

	port->port_identifier = port_id;

	device_initialize(&port->dev);

	port->dev.parent = get_device(parent);
	port->dev.release = sas_port_release;

	mutex_init(&port->phy_list_mutex);
	INIT_LIST_HEAD(&port->phy_list);

	if (scsi_is_sas_expander_device(parent)) {
		struct sas_rphy *rphy = dev_to_rphy(parent);
		dev_set_name(&port->dev, "port-%d:%d:%d", shost->host_no,
			     rphy->scsi_target_id, port->port_identifier);
	} else
		dev_set_name(&port->dev, "port-%d:%d", shost->host_no,
			     port->port_identifier);

	transport_setup_device(&port->dev);

	return port;
}