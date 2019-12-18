#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  netfn; } ;
struct TYPE_4__ {scalar_t__* data; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct aem_ipmi_data {int interface; int /*<<< orphan*/  user; TYPE_2__ tx_message; scalar_t__ tx_msgid; TYPE_1__ address; struct device* bmc_device; int /*<<< orphan*/  read_complete; } ;
struct TYPE_6__ {int /*<<< orphan*/  ipmi_hndlrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEM_NETFN ; 
 int EACCES ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_3__ driver_data ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int ipmi_create_user (int,int /*<<< orphan*/ *,struct aem_ipmi_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aem_init_ipmi_data(struct aem_ipmi_data *data, int iface,
			      struct device *bmc)
{
	int err;

	init_completion(&data->read_complete);
	data->bmc_device = bmc;

	/* Initialize IPMI address */
	data->address.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	data->address.channel = IPMI_BMC_CHANNEL;
	data->address.data[0] = 0;
	data->interface = iface;

	/* Initialize message buffers */
	data->tx_msgid = 0;
	data->tx_message.netfn = AEM_NETFN;

	/* Create IPMI messaging interface user */
	err = ipmi_create_user(data->interface, &driver_data.ipmi_hndlrs,
			       data, &data->user);
	if (err < 0) {
		dev_err(bmc, "Unable to register user with IPMI "
			"interface %d\n", data->interface);
		return -EACCES;
	}

	return 0;
}