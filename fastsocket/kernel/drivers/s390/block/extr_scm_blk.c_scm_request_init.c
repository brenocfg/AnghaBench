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
typedef  scalar_t__ u64 ;
struct scm_request {int retries; scalar_t__ error; struct scm_blk_dev* bdev; struct request* request; struct aob* aidaw; struct aob* aob; } ;
struct scm_blk_dev {int /*<<< orphan*/  scmdev; } ;
struct request {int dummy; } ;
struct aob_rq_header {int /*<<< orphan*/  scmdev; } ;
struct TYPE_2__ {scalar_t__ data; int /*<<< orphan*/  cmd_code; } ;
struct aob {TYPE_1__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARQB_CMD_MOVE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (struct aob*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scm_request_cluster_init (struct scm_request*) ; 
 struct aob_rq_header* to_aobrq (struct scm_request*) ; 

__attribute__((used)) static inline void scm_request_init(struct scm_blk_dev *bdev,
				    struct scm_request *scmrq,
				    struct request *req)
{
	struct aob_rq_header *aobrq = to_aobrq(scmrq);
	struct aob *aob = scmrq->aob;

	memset(aob, 0, sizeof(*aob));
	memset(scmrq->aidaw, 0, PAGE_SIZE);
	aobrq->scmdev = bdev->scmdev;
	aob->request.cmd_code = ARQB_CMD_MOVE;
	aob->request.data = (u64) aobrq;
	scmrq->request = req;
	scmrq->bdev = bdev;
	scmrq->retries = 4;
	scmrq->error = 0;
	scm_request_cluster_init(scmrq);
}