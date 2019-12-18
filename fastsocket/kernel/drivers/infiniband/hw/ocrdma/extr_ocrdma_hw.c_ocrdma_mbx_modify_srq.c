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
struct ocrdma_srq {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct ocrdma_mqe {int dummy; } ;
struct ocrdma_modify_srq {int limit_max_rqe; int /*<<< orphan*/  id; } ;
struct ib_srq_attr {int srq_limit; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_CREATE_SRQ ; 
 int OCRDMA_MODIFY_SRQ_LIMIT_SHIFT ; 
 int /*<<< orphan*/  kfree (struct ocrdma_modify_srq*) ; 
 struct ocrdma_modify_srq* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (int /*<<< orphan*/ ,struct ocrdma_mqe*) ; 

int ocrdma_mbx_modify_srq(struct ocrdma_srq *srq, struct ib_srq_attr *srq_attr)
{
	int status = -ENOMEM;
	struct ocrdma_modify_srq *cmd;
	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_CREATE_SRQ, sizeof(*cmd));
	if (!cmd)
		return status;
	cmd->id = srq->id;
	cmd->limit_max_rqe |= srq_attr->srq_limit <<
	    OCRDMA_MODIFY_SRQ_LIMIT_SHIFT;
	status = ocrdma_mbx_cmd(srq->dev, (struct ocrdma_mqe *)cmd);
	kfree(cmd);
	return status;
}