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
struct zfcp_dbf_san_record_els {int /*<<< orphan*/  ls_code; } ;
struct zfcp_dbf_san_record_ct_response {int /*<<< orphan*/  max_res_size; int /*<<< orphan*/  vendor_unique; int /*<<< orphan*/  expl; int /*<<< orphan*/  reason_code; int /*<<< orphan*/  revision; int /*<<< orphan*/  cmd_rsp_code; } ;
struct zfcp_dbf_san_record_ct_request {int /*<<< orphan*/  max_res_size; int /*<<< orphan*/  options; int /*<<< orphan*/  gs_subtype; int /*<<< orphan*/  gs_type; int /*<<< orphan*/  revision; int /*<<< orphan*/  cmd_req_code; } ;
struct TYPE_2__ {struct zfcp_dbf_san_record_els els; struct zfcp_dbf_san_record_ct_response ct_resp; struct zfcp_dbf_san_record_ct_request ct_req; } ;
struct zfcp_dbf_san_record {TYPE_1__ u; int /*<<< orphan*/  tag; int /*<<< orphan*/  d_id; int /*<<< orphan*/  s_id; int /*<<< orphan*/  fsf_seqno; int /*<<< orphan*/  fsf_reqid; } ;
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_tag (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_dbf_san_view_format(debug_info_t *id, struct debug_view *view,
				    char *out_buf, const char *in_buf)
{
	struct zfcp_dbf_san_record *r = (struct zfcp_dbf_san_record *)in_buf;
	char *p = out_buf;

	if (strncmp(r->tag, "dump", ZFCP_DBF_TAG_SIZE) == 0)
		return 0;

	zfcp_dbf_tag(&p, "tag", r->tag);
	zfcp_dbf_out(&p, "fsf_reqid", "0x%0Lx", r->fsf_reqid);
	zfcp_dbf_out(&p, "fsf_seqno", "0x%08x", r->fsf_seqno);
	zfcp_dbf_out(&p, "s_id", "0x%06x", r->s_id);
	zfcp_dbf_out(&p, "d_id", "0x%06x", r->d_id);

	if (strncmp(r->tag, "octc", ZFCP_DBF_TAG_SIZE) == 0) {
		struct zfcp_dbf_san_record_ct_request *ct = &r->u.ct_req;
		zfcp_dbf_out(&p, "cmd_req_code", "0x%04x", ct->cmd_req_code);
		zfcp_dbf_out(&p, "revision", "0x%02x", ct->revision);
		zfcp_dbf_out(&p, "gs_type", "0x%02x", ct->gs_type);
		zfcp_dbf_out(&p, "gs_subtype", "0x%02x", ct->gs_subtype);
		zfcp_dbf_out(&p, "options", "0x%02x", ct->options);
		zfcp_dbf_out(&p, "max_res_size", "0x%04x", ct->max_res_size);
	} else if (strncmp(r->tag, "rctc", ZFCP_DBF_TAG_SIZE) == 0) {
		struct zfcp_dbf_san_record_ct_response *ct = &r->u.ct_resp;
		zfcp_dbf_out(&p, "cmd_rsp_code", "0x%04x", ct->cmd_rsp_code);
		zfcp_dbf_out(&p, "revision", "0x%02x", ct->revision);
		zfcp_dbf_out(&p, "reason_code", "0x%02x", ct->reason_code);
		zfcp_dbf_out(&p, "reason_code_expl", "0x%02x", ct->expl);
		zfcp_dbf_out(&p, "vendor_unique", "0x%02x", ct->vendor_unique);
		zfcp_dbf_out(&p, "max_res_size", "0x%04x", ct->max_res_size);
	} else if (strncmp(r->tag, "oels", ZFCP_DBF_TAG_SIZE) == 0 ||
		   strncmp(r->tag, "rels", ZFCP_DBF_TAG_SIZE) == 0 ||
		   strncmp(r->tag, "iels", ZFCP_DBF_TAG_SIZE) == 0) {
		struct zfcp_dbf_san_record_els *els = &r->u.els;
		zfcp_dbf_out(&p, "ls_code", "0x%02x", els->ls_code);
	}
	return p - out_buf;
}