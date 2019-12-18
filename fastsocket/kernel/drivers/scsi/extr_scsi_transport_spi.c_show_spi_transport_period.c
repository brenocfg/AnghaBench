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
struct spi_transport_attrs {int /*<<< orphan*/  period; } ;
struct spi_internal {TYPE_2__* f; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int /*<<< orphan*/  starget_data; TYPE_1__ dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_period ) (struct scsi_target*) ;} ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_spi_transport_period_helper (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_target*) ; 
 struct spi_internal* to_spi_internal (int /*<<< orphan*/ ) ; 
 struct scsi_target* transport_class_to_starget (struct device*) ; 

__attribute__((used)) static ssize_t
show_spi_transport_period(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct scsi_target *starget = transport_class_to_starget(dev);
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct spi_internal *i = to_spi_internal(shost->transportt);
	struct spi_transport_attrs *tp =
		(struct spi_transport_attrs *)&starget->starget_data;

	if (i->f->get_period)
		i->f->get_period(starget);

	return show_spi_transport_period_helper(buf, tp->period);
}