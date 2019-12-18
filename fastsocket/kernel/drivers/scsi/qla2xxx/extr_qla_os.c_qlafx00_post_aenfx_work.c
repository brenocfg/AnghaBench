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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int dummy; } ;
struct TYPE_3__ {int count; int /*<<< orphan*/  mbx; int /*<<< orphan*/  evtcode; } ;
struct TYPE_4__ {TYPE_1__ aenfx; } ;
struct qla_work_evt {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_EVT_AENFX ; 
 int QLA_FUNCTION_FAILED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct qla_work_evt* qla2x00_alloc_work (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla2x00_post_work (struct scsi_qla_host*,struct qla_work_evt*) ; 

int
qlafx00_post_aenfx_work(struct scsi_qla_host *vha,  uint32_t evtcode,
			uint32_t *data, int cnt)
{
	struct qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_AENFX);
	if (!e)
		return QLA_FUNCTION_FAILED;

	e->u.aenfx.evtcode = evtcode;
	e->u.aenfx.count = cnt;
	memcpy(e->u.aenfx.mbx, data, sizeof(*data) * cnt);
	return qla2x00_post_work(vha, e);
}