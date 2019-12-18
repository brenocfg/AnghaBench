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
typedef  int /*<<< orphan*/  uint8_t ;
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct beiscsi_hba {int dummy; } ;
struct beiscsi_endpoint {int /*<<< orphan*/  openiscsi_ep; int /*<<< orphan*/  ep_cid; struct beiscsi_conn* conn; struct beiscsi_hba* phba; } ;
struct beiscsi_conn {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  BEISCSI_NO_RST_ISSUE ; 
 unsigned short CMD_ISCSI_SESSION_SAVE_CFG_ON_FLASH ; 
 int /*<<< orphan*/  CONNECTION_UPLOAD_ABORT ; 
 int /*<<< orphan*/  CONNECTION_UPLOAD_GRACEFUL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_close_conn (struct beiscsi_endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_free_ep (struct beiscsi_endpoint*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  beiscsi_unbind_conn_to_cid (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_suspend_queue (int /*<<< orphan*/ ) ; 
 unsigned int mgmt_invalidate_connection (struct beiscsi_hba*,struct beiscsi_endpoint*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 

void beiscsi_ep_disconnect(struct iscsi_endpoint *ep)
{
	struct beiscsi_conn *beiscsi_conn;
	struct beiscsi_endpoint *beiscsi_ep;
	struct beiscsi_hba *phba;
	unsigned int tag;
	uint8_t mgmt_invalidate_flag, tcp_upload_flag;
	unsigned short savecfg_flag = CMD_ISCSI_SESSION_SAVE_CFG_ON_FLASH;

	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_ep_disconnect for ep_cid = %d\n",
		    beiscsi_ep->ep_cid);

	if (beiscsi_ep->conn) {
		beiscsi_conn = beiscsi_ep->conn;
		iscsi_suspend_queue(beiscsi_conn->conn);
		mgmt_invalidate_flag = ~BEISCSI_NO_RST_ISSUE;
		tcp_upload_flag = CONNECTION_UPLOAD_GRACEFUL;
	} else {
		mgmt_invalidate_flag = BEISCSI_NO_RST_ISSUE;
		tcp_upload_flag = CONNECTION_UPLOAD_ABORT;
	}

	tag = mgmt_invalidate_connection(phba, beiscsi_ep,
					  beiscsi_ep->ep_cid,
					  mgmt_invalidate_flag,
					  savecfg_flag);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : mgmt_invalidate_connection Failed for cid=%d\n",
			    beiscsi_ep->ep_cid);
	}

	beiscsi_mccq_compl(phba, tag, NULL, NULL);
	beiscsi_close_conn(beiscsi_ep, tcp_upload_flag);
	beiscsi_free_ep(beiscsi_ep);
	beiscsi_unbind_conn_to_cid(phba, beiscsi_ep->ep_cid);
	iscsi_destroy_endpoint(beiscsi_ep->openiscsi_ep);
}