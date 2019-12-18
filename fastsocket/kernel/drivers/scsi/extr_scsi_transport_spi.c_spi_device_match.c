#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spi_internal {TYPE_3__* f; } ;
struct scsi_device {int /*<<< orphan*/  sdev_target; struct Scsi_Host* host; } ;
struct device {int dummy; } ;
struct attribute_container {int dummy; } ;
struct Scsi_Host {TYPE_4__* transportt; } ;
struct TYPE_10__ {int /*<<< orphan*/  class; } ;
struct TYPE_6__ {int /*<<< orphan*/ * class; } ;
struct TYPE_7__ {TYPE_1__ ac; } ;
struct TYPE_9__ {TYPE_2__ host_attrs; } ;
struct TYPE_8__ {scalar_t__ (* deny_binding ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_is_sdev_device (struct device*) ; 
 TYPE_5__ spi_host_class ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 
 struct spi_internal* to_spi_internal (TYPE_4__*) ; 

__attribute__((used)) static int spi_device_match(struct attribute_container *cont,
			    struct device *dev)
{
	struct scsi_device *sdev;
	struct Scsi_Host *shost;
	struct spi_internal *i;

	if (!scsi_is_sdev_device(dev))
		return 0;

	sdev = to_scsi_device(dev);
	shost = sdev->host;
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		return 0;
	/* Note: this class has no device attributes, so it has
	 * no per-HBA allocation and thus we don't need to distinguish
	 * the attribute containers for the device */
	i = to_spi_internal(shost->transportt);
	if (i->f->deny_binding && i->f->deny_binding(sdev->sdev_target))
		return 0;
	return 1;
}