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
struct TYPE_9__ {int /*<<< orphan*/  step; int /*<<< orphan*/  status; int /*<<< orphan*/  fsf_req; int /*<<< orphan*/  action; } ;
struct TYPE_8__ {int /*<<< orphan*/  us; int /*<<< orphan*/  ps; int /*<<< orphan*/  as; int /*<<< orphan*/  fcp_lun; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  need; int /*<<< orphan*/  want; int /*<<< orphan*/  action; int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  fcp_lun; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  d_id; int /*<<< orphan*/  erp_count; int /*<<< orphan*/  status; int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  running; int /*<<< orphan*/  ready; int /*<<< orphan*/  total; } ;
struct TYPE_10__ {TYPE_4__ action; TYPE_3__ trigger; TYPE_2__ target; TYPE_1__ thread; } ;
struct zfcp_dbf_rec_record {size_t id; TYPE_5__ u; int /*<<< orphan*/  id2; } ;
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;

/* Variables and functions */
 int ZFCP_DBF_ID_SIZE ; 
#define  ZFCP_REC_DBF_ID_ACTION 131 
#define  ZFCP_REC_DBF_ID_TARGET 130 
#define  ZFCP_REC_DBF_ID_THREAD 129 
#define  ZFCP_REC_DBF_ID_TRIGGER 128 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_outs (char**,char*,char*) ; 
 char** zfcp_dbf_rec_tags ; 

__attribute__((used)) static int zfcp_dbf_rec_view_format(debug_info_t *id, struct debug_view *view,
				    char *buf, const char *_rec)
{
	struct zfcp_dbf_rec_record *r = (struct zfcp_dbf_rec_record *)_rec;
	char *p = buf;
	char hint[ZFCP_DBF_ID_SIZE + 1];

	memcpy(hint, r->id2, ZFCP_DBF_ID_SIZE);
	hint[ZFCP_DBF_ID_SIZE] = 0;
	zfcp_dbf_outs(&p, "tag", zfcp_dbf_rec_tags[r->id]);
	zfcp_dbf_outs(&p, "hint", hint);
	switch (r->id) {
	case ZFCP_REC_DBF_ID_THREAD:
		zfcp_dbf_out(&p, "total", "%d", r->u.thread.total);
		zfcp_dbf_out(&p, "ready", "%d", r->u.thread.ready);
		zfcp_dbf_out(&p, "running", "%d", r->u.thread.running);
		break;
	case ZFCP_REC_DBF_ID_TARGET:
		zfcp_dbf_out(&p, "reference", "0x%016Lx", r->u.target.ref);
		zfcp_dbf_out(&p, "status", "0x%08x", r->u.target.status);
		zfcp_dbf_out(&p, "erp_count", "%d", r->u.target.erp_count);
		zfcp_dbf_out(&p, "d_id", "0x%06x", r->u.target.d_id);
		zfcp_dbf_out(&p, "wwpn", "0x%016Lx", r->u.target.wwpn);
		zfcp_dbf_out(&p, "fcp_lun", "0x%016Lx", r->u.target.fcp_lun);
		break;
	case ZFCP_REC_DBF_ID_TRIGGER:
		zfcp_dbf_out(&p, "reference", "0x%016Lx", r->u.trigger.ref);
		zfcp_dbf_out(&p, "erp_action", "0x%016Lx", r->u.trigger.action);
		zfcp_dbf_out(&p, "requested", "%d", r->u.trigger.want);
		zfcp_dbf_out(&p, "executed", "%d", r->u.trigger.need);
		zfcp_dbf_out(&p, "wwpn", "0x%016Lx", r->u.trigger.wwpn);
		zfcp_dbf_out(&p, "fcp_lun", "0x%016Lx", r->u.trigger.fcp_lun);
		zfcp_dbf_out(&p, "adapter_status", "0x%08x", r->u.trigger.as);
		zfcp_dbf_out(&p, "port_status", "0x%08x", r->u.trigger.ps);
		zfcp_dbf_out(&p, "unit_status", "0x%08x", r->u.trigger.us);
		break;
	case ZFCP_REC_DBF_ID_ACTION:
		zfcp_dbf_out(&p, "erp_action", "0x%016Lx", r->u.action.action);
		zfcp_dbf_out(&p, "fsf_req", "0x%016Lx", r->u.action.fsf_req);
		zfcp_dbf_out(&p, "status", "0x%08Lx", r->u.action.status);
		zfcp_dbf_out(&p, "step", "0x%08Lx", r->u.action.step);
		break;
	}
	p += sprintf(p, "\n");
	return p - buf;
}