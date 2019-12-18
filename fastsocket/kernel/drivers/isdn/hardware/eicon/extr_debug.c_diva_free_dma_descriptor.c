#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int descriptor_number; scalar_t__ descriptor_magic; int /*<<< orphan*/ * descriptor_address; int /*<<< orphan*/  operation; } ;
struct TYPE_5__ {TYPE_1__ info; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_6__ {TYPE_2__ xdi_dma_descriptor_operation; } ;
typedef  TYPE_3__ IDI_SYNC_REQ ;
typedef  int /*<<< orphan*/  (* IDI_CALL ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  IDI_SYNC_REQ_DMA_DESCRIPTOR_FREE ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_DMA_DESCRIPTOR_OPERATION ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void diva_free_dma_descriptor (IDI_CALL request, int nr) {
  ENTITY e;
  IDI_SYNC_REQ* pReq = (IDI_SYNC_REQ*)&e;

  if (!request || (nr < 0)) {
    return;
  }

  pReq->xdi_dma_descriptor_operation.Req = 0;
  pReq->xdi_dma_descriptor_operation.Rc = IDI_SYNC_REQ_DMA_DESCRIPTOR_OPERATION;

  pReq->xdi_dma_descriptor_operation.info.operation = IDI_SYNC_REQ_DMA_DESCRIPTOR_FREE;
  pReq->xdi_dma_descriptor_operation.info.descriptor_number  = nr;
  pReq->xdi_dma_descriptor_operation.info.descriptor_address = NULL;
  pReq->xdi_dma_descriptor_operation.info.descriptor_magic   = 0;

  (*request)((ENTITY*)pReq);
}