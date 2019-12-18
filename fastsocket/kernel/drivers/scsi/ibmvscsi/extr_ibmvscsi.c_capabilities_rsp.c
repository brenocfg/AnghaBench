#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct srp_event_struct {TYPE_1__* xfer_iu; struct ibmvscsi_host_data* hostdata; } ;
struct TYPE_13__ {scalar_t__ server_support; } ;
struct TYPE_14__ {TYPE_4__ common; } ;
struct TYPE_11__ {scalar_t__ server_support; } ;
struct TYPE_12__ {TYPE_2__ common; } ;
struct TYPE_15__ {TYPE_5__ reserve; TYPE_3__ migration; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; TYPE_6__ caps; } ;
struct TYPE_17__ {int /*<<< orphan*/  status; } ;
struct TYPE_16__ {TYPE_8__ common; } ;
struct TYPE_18__ {TYPE_7__ capabilities; } ;
struct TYPE_10__ {TYPE_9__ mad; } ;

/* Variables and functions */
 scalar_t__ SERVER_SUPPORTS_CAP ; 
 scalar_t__ client_reserve ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send_srp_login (struct ibmvscsi_host_data*) ; 

__attribute__((used)) static void capabilities_rsp(struct srp_event_struct *evt_struct)
{
	struct ibmvscsi_host_data *hostdata = evt_struct->hostdata;

	if (evt_struct->xfer_iu->mad.capabilities.common.status) {
		dev_err(hostdata->dev, "error 0x%X getting capabilities info\n",
			evt_struct->xfer_iu->mad.capabilities.common.status);
	} else {
		if (hostdata->caps.migration.common.server_support != SERVER_SUPPORTS_CAP)
			dev_info(hostdata->dev, "Partition migration not supported\n");

		if (client_reserve) {
			if (hostdata->caps.reserve.common.server_support ==
			    SERVER_SUPPORTS_CAP)
				dev_info(hostdata->dev, "Client reserve enabled\n");
			else
				dev_info(hostdata->dev, "Client reserve not supported\n");
		}
	}

	send_srp_login(hostdata);
}