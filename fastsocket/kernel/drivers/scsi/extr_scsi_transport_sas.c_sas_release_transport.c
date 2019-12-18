#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_transport_template {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_attrs; } ;
struct sas_internal {int /*<<< orphan*/  expander_attr_cont; int /*<<< orphan*/  end_dev_attr_cont; int /*<<< orphan*/  rphy_attr_cont; int /*<<< orphan*/  port_attr_cont; int /*<<< orphan*/  phy_attr_cont; TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sas_internal*) ; 
 struct sas_internal* to_sas_internal (struct scsi_transport_template*) ; 
 int /*<<< orphan*/  transport_container_unregister (int /*<<< orphan*/ *) ; 

void sas_release_transport(struct scsi_transport_template *t)
{
	struct sas_internal *i = to_sas_internal(t);

	transport_container_unregister(&i->t.host_attrs);
	transport_container_unregister(&i->phy_attr_cont);
	transport_container_unregister(&i->port_attr_cont);
	transport_container_unregister(&i->rphy_attr_cont);
	transport_container_unregister(&i->end_dev_attr_cont);
	transport_container_unregister(&i->expander_attr_cont);

	kfree(i);
}