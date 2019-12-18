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
struct attribute_container {int dummy; } ;
struct TYPE_6__ {struct attribute_container ac; } ;
struct fc_internal {TYPE_1__ rport_attr_cont; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct Scsi_Host {TYPE_4__* transportt; } ;
struct TYPE_10__ {int /*<<< orphan*/  class; } ;
struct TYPE_7__ {int /*<<< orphan*/ * class; } ;
struct TYPE_8__ {TYPE_2__ ac; } ;
struct TYPE_9__ {TYPE_3__ host_attrs; } ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 TYPE_5__ fc_host_class ; 
 int /*<<< orphan*/  scsi_is_fc_rport (struct device*) ; 
 struct fc_internal* to_fc_internal (TYPE_4__*) ; 

__attribute__((used)) static int fc_rport_match(struct attribute_container *cont,
			    struct device *dev)
{
	struct Scsi_Host *shost;
	struct fc_internal *i;

	if (!scsi_is_fc_rport(dev))
		return 0;

	shost = dev_to_shost(dev->parent);
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &fc_host_class.class)
		return 0;

	i = to_fc_internal(shost->transportt);

	return &i->rport_attr_cont.ac == cont;
}