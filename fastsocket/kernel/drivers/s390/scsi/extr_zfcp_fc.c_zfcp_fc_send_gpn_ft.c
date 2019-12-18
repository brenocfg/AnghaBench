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
struct zfcp_send_ct {unsigned long handler_data; int /*<<< orphan*/  resp; int /*<<< orphan*/ * req; int /*<<< orphan*/  handler; int /*<<< orphan*/ * wka_port; } ;
struct zfcp_gpn_ft {int /*<<< orphan*/  sg_resp; int /*<<< orphan*/  sg_req; struct zfcp_send_ct ct; } ;
struct zfcp_fc_ns_handler_data {int /*<<< orphan*/  done; int /*<<< orphan*/ * handler; } ;
struct zfcp_adapter {TYPE_2__* gs; } ;
struct TYPE_3__ {int max_res_size; int /*<<< orphan*/  cmd_rsp_code; int /*<<< orphan*/  options; int /*<<< orphan*/  gs_subtype; int /*<<< orphan*/  gs_type; int /*<<< orphan*/  revision; } ;
struct ct_iu_gpn_ft_req {int /*<<< orphan*/  fc4_type; scalar_t__ area_id_scope; scalar_t__ domain_id_scope; scalar_t__ flags; TYPE_1__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_CT_DIRECTORY_SERVICE ; 
 int /*<<< orphan*/  ZFCP_CT_GPN_FT ; 
 int /*<<< orphan*/  ZFCP_CT_NAME_SERVER ; 
 int /*<<< orphan*/  ZFCP_CT_REVISION ; 
 int /*<<< orphan*/  ZFCP_CT_SCSI_FCP ; 
 int /*<<< orphan*/  ZFCP_CT_SYNCHRONOUS ; 
 int /*<<< orphan*/  ZFCP_FC_CTELS_TMO ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct ct_iu_gpn_ft_req* sg_virt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_ns_handler ; 
 int zfcp_fsf_send_ct (struct zfcp_send_ct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_fc_send_gpn_ft(struct zfcp_gpn_ft *gpn_ft,
			       struct zfcp_adapter *adapter, int max_bytes)
{
	struct zfcp_send_ct *ct = &gpn_ft->ct;
	struct ct_iu_gpn_ft_req *req = sg_virt(&gpn_ft->sg_req);
	struct zfcp_fc_ns_handler_data compl_rec;
	int ret;

	/* prepare CT IU for GPN_FT */
	req->header.revision = ZFCP_CT_REVISION;
	req->header.gs_type = ZFCP_CT_DIRECTORY_SERVICE;
	req->header.gs_subtype = ZFCP_CT_NAME_SERVER;
	req->header.options = ZFCP_CT_SYNCHRONOUS;
	req->header.cmd_rsp_code = ZFCP_CT_GPN_FT;
	req->header.max_res_size = max_bytes / 4;
	req->flags = 0;
	req->domain_id_scope = 0;
	req->area_id_scope = 0;
	req->fc4_type = ZFCP_CT_SCSI_FCP;

	/* prepare zfcp_send_ct */
	ct->wka_port = &adapter->gs->ds;
	ct->handler = zfcp_fc_ns_handler;
	ct->handler_data = (unsigned long)&compl_rec;
	ct->req = &gpn_ft->sg_req;
	ct->resp = gpn_ft->sg_resp;

	init_completion(&compl_rec.done);
	compl_rec.handler = NULL;
	ret = zfcp_fsf_send_ct(ct, NULL, ZFCP_FC_CTELS_TMO);
	if (!ret)
		wait_for_completion(&compl_rec.done);
	return ret;
}