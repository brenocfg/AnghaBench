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
struct zfcp_port {int /*<<< orphan*/  wwpn; struct zfcp_adapter* adapter; } ;
struct TYPE_9__ {unsigned long handler_data; int /*<<< orphan*/ * resp; int /*<<< orphan*/ * req; int /*<<< orphan*/  handler; int /*<<< orphan*/ * wka_port; } ;
struct TYPE_7__ {int max_res_size; int /*<<< orphan*/  cmd_rsp_code; int /*<<< orphan*/  options; int /*<<< orphan*/  gs_subtype; int /*<<< orphan*/  gs_type; int /*<<< orphan*/  revision; } ;
struct TYPE_10__ {int /*<<< orphan*/  wwpn; TYPE_2__ header; } ;
struct zfcp_gid_pn_data {TYPE_4__ ct; TYPE_5__ ct_iu_req; TYPE_5__ ct_iu_resp; int /*<<< orphan*/  resp; int /*<<< orphan*/  req; struct zfcp_port* port; } ;
struct zfcp_fc_ns_handler_data {unsigned long handler_data; int /*<<< orphan*/  done; int /*<<< orphan*/  handler; } ;
struct TYPE_8__ {int /*<<< orphan*/  gid_pn_req; } ;
struct zfcp_adapter {TYPE_3__ pool; TYPE_1__* gs; } ;
struct ct_iu_gid_pn_resp {int dummy; } ;
struct ct_iu_gid_pn_req {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_CT_DIRECTORY_SERVICE ; 
 int /*<<< orphan*/  ZFCP_CT_GID_PN ; 
 int /*<<< orphan*/  ZFCP_CT_NAME_SERVER ; 
 int /*<<< orphan*/  ZFCP_CT_REVISION ; 
 int ZFCP_CT_SIZE_ONE_PAGE ; 
 int /*<<< orphan*/  ZFCP_CT_SYNCHRONOUS ; 
 int /*<<< orphan*/  ZFCP_FC_CTELS_TMO ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_ns_gid_pn_eval ; 
 int /*<<< orphan*/  zfcp_fc_ns_handler ; 
 int zfcp_fsf_send_ct (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_fc_ns_gid_pn_request(struct zfcp_port *port,
				     struct zfcp_gid_pn_data *gid_pn)
{
	struct zfcp_adapter *adapter = port->adapter;
	struct zfcp_fc_ns_handler_data compl_rec;
	int ret;

	/* setup parameters for send generic command */
	gid_pn->port = port;
	gid_pn->ct.wka_port = &adapter->gs->ds;
	gid_pn->ct.handler = zfcp_fc_ns_handler;
	gid_pn->ct.handler_data = (unsigned long) &compl_rec;
	gid_pn->ct.req = &gid_pn->req;
	gid_pn->ct.resp = &gid_pn->resp;
	sg_init_one(&gid_pn->req, &gid_pn->ct_iu_req,
		    sizeof(struct ct_iu_gid_pn_req));
	sg_init_one(&gid_pn->resp, &gid_pn->ct_iu_resp,
		    sizeof(struct ct_iu_gid_pn_resp));

	/* setup nameserver request */
	gid_pn->ct_iu_req.header.revision = ZFCP_CT_REVISION;
	gid_pn->ct_iu_req.header.gs_type = ZFCP_CT_DIRECTORY_SERVICE;
	gid_pn->ct_iu_req.header.gs_subtype = ZFCP_CT_NAME_SERVER;
	gid_pn->ct_iu_req.header.options = ZFCP_CT_SYNCHRONOUS;
	gid_pn->ct_iu_req.header.cmd_rsp_code = ZFCP_CT_GID_PN;
	gid_pn->ct_iu_req.header.max_res_size = ZFCP_CT_SIZE_ONE_PAGE / 4;
	gid_pn->ct_iu_req.wwpn = port->wwpn;

	init_completion(&compl_rec.done);
	compl_rec.handler = zfcp_fc_ns_gid_pn_eval;
	compl_rec.handler_data = (unsigned long) gid_pn;
	ret = zfcp_fsf_send_ct(&gid_pn->ct, adapter->pool.gid_pn_req,
			       ZFCP_FC_CTELS_TMO);
	if (!ret)
		wait_for_completion(&compl_rec.done);
	return ret;
}