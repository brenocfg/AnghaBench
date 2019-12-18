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
typedef  size_t u8 ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_get_port_name {size_t* port_name; } ;
struct TYPE_2__ {int version; } ;
struct be_cmd_req_get_port_name {TYPE_1__ hdr; } ;
struct be_adapter {size_t hba_port_num; int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_GET_PORT_NAME ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_query_port_name(struct be_adapter *adapter, u8 *port_name)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_get_port_name *req;
	int status;

	if (!lancer_chip(adapter)) {
		*port_name = adapter->hba_port_num + '0';
		return 0;
	}

	spin_lock_bh(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}

	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_GET_PORT_NAME, sizeof(*req), wrb,
			       NULL);
	req->hdr.version = 1;

	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_get_port_name *resp = embedded_payload(wrb);
		*port_name = resp->port_name[adapter->hba_port_num];
	} else {
		*port_name = adapter->hba_port_num + '0';
	}
err:
	spin_unlock_bh(&adapter->mcc_lock);
	return status;
}