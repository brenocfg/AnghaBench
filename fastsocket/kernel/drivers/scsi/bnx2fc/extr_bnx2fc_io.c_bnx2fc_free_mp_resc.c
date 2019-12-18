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
struct fcoe_bd_ctx {int dummy; } ;
struct bnx2fc_mp_req {int /*<<< orphan*/ * resp_buf; int /*<<< orphan*/  resp_buf_dma; int /*<<< orphan*/ * req_buf; int /*<<< orphan*/  req_buf_dma; int /*<<< orphan*/ * mp_resp_bd; int /*<<< orphan*/  mp_resp_bd_dma; int /*<<< orphan*/ * mp_req_bd; int /*<<< orphan*/  mp_req_bd_dma; scalar_t__ tm_flags; } ;
struct bnx2fc_interface {struct bnx2fc_hba* hba; } ;
struct bnx2fc_hba {TYPE_2__* pcidev; } ;
struct bnx2fc_cmd {TYPE_1__* port; struct bnx2fc_mp_req mp_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct bnx2fc_interface* priv; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2fc_free_mp_resc(struct bnx2fc_cmd *io_req)
{
	struct bnx2fc_mp_req *mp_req = &(io_req->mp_req);
	struct bnx2fc_interface *interface = io_req->port->priv;
	struct bnx2fc_hba *hba = interface->hba;
	size_t sz = sizeof(struct fcoe_bd_ctx);

	/* clear tm flags */
	mp_req->tm_flags = 0;
	if (mp_req->mp_req_bd) {
		dma_free_coherent(&hba->pcidev->dev, sz,
				     mp_req->mp_req_bd,
				     mp_req->mp_req_bd_dma);
		mp_req->mp_req_bd = NULL;
	}
	if (mp_req->mp_resp_bd) {
		dma_free_coherent(&hba->pcidev->dev, sz,
				     mp_req->mp_resp_bd,
				     mp_req->mp_resp_bd_dma);
		mp_req->mp_resp_bd = NULL;
	}
	if (mp_req->req_buf) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				     mp_req->req_buf,
				     mp_req->req_buf_dma);
		mp_req->req_buf = NULL;
	}
	if (mp_req->resp_buf) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				     mp_req->resp_buf,
				     mp_req->resp_buf_dma);
		mp_req->resp_buf = NULL;
	}
}