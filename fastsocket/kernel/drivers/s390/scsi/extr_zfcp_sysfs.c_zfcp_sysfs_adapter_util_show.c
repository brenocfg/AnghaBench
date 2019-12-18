#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct zfcp_adapter {int adapter_features; int /*<<< orphan*/  qdio; } ;
struct fsf_qtcb_bottom_port {int cp_util; int cb_util; int a_util; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int FSF_FEATURE_MEASUREMENT_DATA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  kfree (struct fsf_qtcb_bottom_port*) ; 
 struct fsf_qtcb_bottom_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int,int,int) ; 
 int zfcp_fsf_exchange_port_data_sync (int /*<<< orphan*/ ,struct fsf_qtcb_bottom_port*) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_adapter_util_show(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct Scsi_Host *scsi_host = dev_to_shost(dev);
	struct fsf_qtcb_bottom_port *qtcb_port;
	struct zfcp_adapter *adapter;
	int retval;

	adapter = (struct zfcp_adapter *) scsi_host->hostdata[0];
	if (!(adapter->adapter_features & FSF_FEATURE_MEASUREMENT_DATA))
		return -EOPNOTSUPP;

	qtcb_port = kzalloc(sizeof(struct fsf_qtcb_bottom_port), GFP_KERNEL);
	if (!qtcb_port)
		return -ENOMEM;

	retval = zfcp_fsf_exchange_port_data_sync(adapter->qdio, qtcb_port);
	if (!retval)
		retval = sprintf(buf, "%u %u %u\n", qtcb_port->cp_util,
				 qtcb_port->cb_util, qtcb_port->a_util);
	kfree(qtcb_port);
	return retval;
}