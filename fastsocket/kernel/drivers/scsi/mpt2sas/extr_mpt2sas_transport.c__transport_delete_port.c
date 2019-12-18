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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int device_type; scalar_t__ sas_address; } ;
struct _sas_port {TYPE_2__* port; TYPE_1__ remote_identify; } ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  logging_level; } ;
typedef  enum sas_device_type { ____Placeholder_sas_device_type } sas_device_type ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MPT_DEBUG_TRANSPORT ; 
 int SAS_EDGE_EXPANDER_DEVICE ; 
 int SAS_END_DEVICE ; 
 int SAS_FANOUT_EXPANDER_DEVICE ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  mpt2sas_device_remove_by_sas_address (struct MPT2SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  mpt2sas_expander_remove (struct MPT2SAS_ADAPTER*,scalar_t__) ; 

__attribute__((used)) static void
_transport_delete_port(struct MPT2SAS_ADAPTER *ioc,
	struct _sas_port *mpt2sas_port)
{
	u64 sas_address = mpt2sas_port->remote_identify.sas_address;
	enum sas_device_type device_type =
	    mpt2sas_port->remote_identify.device_type;

	dev_printk(KERN_INFO, &mpt2sas_port->port->dev,
	    "remove: sas_addr(0x%016llx)\n",
	    (unsigned long long) sas_address);

	ioc->logging_level |= MPT_DEBUG_TRANSPORT;
	if (device_type == SAS_END_DEVICE)
		mpt2sas_device_remove_by_sas_address(ioc, sas_address);
	else if (device_type == SAS_EDGE_EXPANDER_DEVICE ||
	    device_type == SAS_FANOUT_EXPANDER_DEVICE)
		mpt2sas_expander_remove(ioc, sas_address);
	ioc->logging_level &= ~MPT_DEBUG_TRANSPORT;
}