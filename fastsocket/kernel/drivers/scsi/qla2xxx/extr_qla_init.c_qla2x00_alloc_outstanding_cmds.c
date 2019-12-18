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
struct req_que {int num_outstanding_cmds; void* outstanding_cmds; } ;
struct qla_hw_data {int fw_xcb_count; int fw_iocb_count; scalar_t__ mqiobase; } ;
typedef  int /*<<< orphan*/  srb_t ;

/* Variables and functions */
 int DEFAULT_OUTSTANDING_COMMANDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int MIN_OUTSTANDING_COMMANDS ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,int) ; 
 int ql2xmaxqueues ; 
 scalar_t__ ql2xmultique_tag ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,struct req_que*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 

int
qla2x00_alloc_outstanding_cmds(struct qla_hw_data *ha, struct req_que *req)
{
	/* Don't try to reallocate the array */
	if (req->outstanding_cmds)
		return QLA_SUCCESS;

	/*
	 * If we have multiple request queues per adapter or are an ISP23xx or
	 * older, then allocate the old default value.  Otherwise, base the
	 * allocation size on the returned firmware resource counts.
	 */ 
	if (!IS_FWI2_CAPABLE(ha) || (ha->mqiobase &&
	    (ql2xmultique_tag || ql2xmaxqueues > 1)))
		req->num_outstanding_cmds = DEFAULT_OUTSTANDING_COMMANDS;
	else {
		if (min(ha->fw_xcb_count, ha->fw_iocb_count))
			req->num_outstanding_cmds = ha->fw_xcb_count;
		else
			req->num_outstanding_cmds = ha->fw_iocb_count;
	}

	req->outstanding_cmds = kzalloc(sizeof(srb_t *) *
	    req->num_outstanding_cmds, GFP_KERNEL);

	if (!req->outstanding_cmds) {
		/*
		 * Try to allocate a minimal size just so we can get through
		 * initialization.
		 */
		req->num_outstanding_cmds = MIN_OUTSTANDING_COMMANDS;
		req->outstanding_cmds = kzalloc(sizeof(srb_t *) *
		    req->num_outstanding_cmds, GFP_KERNEL);

		if (!req->outstanding_cmds) {
			ql_log(ql_log_fatal, NULL, 0x0123,
			    "Failed to allocate memory for "
			    "outstanding_cmds for req_que %p.\n", req);
			req->num_outstanding_cmds = 0;
			return QLA_FUNCTION_FAILED;
		}
	}

	return QLA_SUCCESS;
}