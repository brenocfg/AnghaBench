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
struct spi_transport_attrs {int min_period; } ;
struct spi_internal {TYPE_1__* f; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int /*<<< orphan*/  starget_data; TYPE_2__ dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_period ) (struct scsi_target*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int store_spi_transport_period_helper (struct device*,char const*,size_t,int*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_target*,int) ; 
 struct spi_internal* to_spi_internal (int /*<<< orphan*/ ) ; 
 struct scsi_target* transport_class_to_starget (struct device*) ; 

__attribute__((used)) static ssize_t
store_spi_transport_period(struct device *cdev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct scsi_target *starget = transport_class_to_starget(cdev);
	struct Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	struct spi_internal *i = to_spi_internal(shost->transportt);
	struct spi_transport_attrs *tp =
		(struct spi_transport_attrs *)&starget->starget_data;
	int period, retval;

	if (!i->f->set_period)
		return -EINVAL;

	retval = store_spi_transport_period_helper(cdev, buf, count, &period);

	if (period < tp->min_period)
		period = tp->min_period;

	i->f->set_period(starget, period);

	return retval;
}