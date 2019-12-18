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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct sas_phy {int enabled; TYPE_1__ dev; } ;
struct sas_internal {TYPE_2__* f; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int (* phy_enable ) (struct sas_phy*,int) ;} ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int stub1 (struct sas_phy*,int) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 
 struct sas_phy* transport_class_to_phy (struct device*) ; 

__attribute__((used)) static ssize_t do_sas_phy_enable(struct device *dev,
		size_t count, int enable)
{
	struct sas_phy *phy = transport_class_to_phy(dev);
	struct Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	struct sas_internal *i = to_sas_internal(shost->transportt);
	int error;

	error = i->f->phy_enable(phy, enable);
	if (error)
		return error;
	phy->enabled = enable;
	return count;
}