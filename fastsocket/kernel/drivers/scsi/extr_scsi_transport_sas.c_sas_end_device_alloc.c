#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  device_type; } ;
struct sas_rphy {TYPE_2__ dev; TYPE_1__ identify; int /*<<< orphan*/  scsi_target_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct sas_port {int /*<<< orphan*/  port_identifier; TYPE_3__ dev; } ;
struct sas_end_device {struct sas_rphy rphy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (TYPE_3__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  get_device (TYPE_3__*) ; 
 struct sas_end_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_end_device_release ; 
 int /*<<< orphan*/  sas_rphy_initialize (struct sas_rphy*) ; 
 scalar_t__ scsi_is_sas_expander_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_setup_device (TYPE_2__*) ; 

struct sas_rphy *sas_end_device_alloc(struct sas_port *parent)
{
	struct Scsi_Host *shost = dev_to_shost(&parent->dev);
	struct sas_end_device *rdev;

	rdev = kzalloc(sizeof(*rdev), GFP_KERNEL);
	if (!rdev) {
		return NULL;
	}

	device_initialize(&rdev->rphy.dev);
	rdev->rphy.dev.parent = get_device(&parent->dev);
	rdev->rphy.dev.release = sas_end_device_release;
	if (scsi_is_sas_expander_device(parent->dev.parent)) {
		struct sas_rphy *rphy = dev_to_rphy(parent->dev.parent);
		dev_set_name(&rdev->rphy.dev, "end_device-%d:%d:%d",
			     shost->host_no, rphy->scsi_target_id,
			     parent->port_identifier);
	} else
		dev_set_name(&rdev->rphy.dev, "end_device-%d:%d",
			     shost->host_no, parent->port_identifier);
	rdev->rphy.identify.device_type = SAS_END_DEVICE;
	sas_rphy_initialize(&rdev->rphy);
	transport_setup_device(&rdev->rphy.dev);

	return &rdev->rphy;
}