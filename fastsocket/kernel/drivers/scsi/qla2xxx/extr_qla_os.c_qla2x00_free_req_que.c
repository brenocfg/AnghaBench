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
struct req_que {int length_fx00; int length; struct req_que* outstanding_cmds; int /*<<< orphan*/  dma; scalar_t__ ring; int /*<<< orphan*/  dma_fx00; scalar_t__ ring_fx00; } ;
struct qla_hw_data {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  request_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct req_que*) ; 

__attribute__((used)) static void qla2x00_free_req_que(struct qla_hw_data *ha, struct req_que *req)
{
	if (IS_QLAFX00(ha)) {
		if (req && req->ring_fx00)
			dma_free_coherent(&ha->pdev->dev,
			    (req->length_fx00 + 1) * sizeof(request_t),
			    req->ring_fx00, req->dma_fx00);
	} else if (req && req->ring)
		dma_free_coherent(&ha->pdev->dev,
		(req->length + 1) * sizeof(request_t),
		req->ring, req->dma);

	if (req && req->outstanding_cmds)
		kfree(req->outstanding_cmds);

	kfree(req);
	req = NULL;
}