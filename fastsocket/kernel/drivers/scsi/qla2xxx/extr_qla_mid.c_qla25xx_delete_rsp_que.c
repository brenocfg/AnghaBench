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
struct scsi_qla_host {int dummy; } ;
struct rsp_que {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_0 ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  qla25xx_free_rsp_que (struct scsi_qla_host*,struct rsp_que*) ; 
 int qla25xx_init_rsp_que (struct scsi_qla_host*,struct rsp_que*) ; 

__attribute__((used)) static int
qla25xx_delete_rsp_que(struct scsi_qla_host *vha, struct rsp_que *rsp)
{
	int ret = -1;

	if (rsp) {
		rsp->options |= BIT_0;
		ret = qla25xx_init_rsp_que(vha, rsp);
	}
	if (ret == QLA_SUCCESS)
		qla25xx_free_rsp_que(vha, rsp);

	return ret;
}