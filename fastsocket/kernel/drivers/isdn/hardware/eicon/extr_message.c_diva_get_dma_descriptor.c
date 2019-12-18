#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dword ;
struct TYPE_14__ {scalar_t__* user; } ;
struct TYPE_10__ {int descriptor_number; scalar_t__ descriptor_magic; int /*<<< orphan*/  operation; int /*<<< orphan*/ * descriptor_address; } ;
struct TYPE_11__ {TYPE_2__ info; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_13__ {TYPE_3__ xdi_dma_descriptor_operation; } ;
struct TYPE_12__ {TYPE_1__* adapter; } ;
struct TYPE_9__ {scalar_t__ Id; int /*<<< orphan*/  (* request ) (TYPE_6__*) ;} ;
typedef  TYPE_4__ PLCI ;
typedef  TYPE_5__ IDI_SYNC_REQ ;
typedef  TYPE_6__ ENTITY ;

/* Variables and functions */
 int DIVA_CAPI_XDI_PROVIDES_RX_DMA ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_DMA_DESCRIPTOR_ALLOC ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_DMA_DESCRIPTOR_OPERATION ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int diva_xdi_extended_features ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

__attribute__((used)) static int diva_get_dma_descriptor (PLCI   *plci, dword   *dma_magic) {
  ENTITY e;
  IDI_SYNC_REQ* pReq = (IDI_SYNC_REQ*)&e;

  if (!(diva_xdi_extended_features & DIVA_CAPI_XDI_PROVIDES_RX_DMA)) {
    return (-1);
  }

  pReq->xdi_dma_descriptor_operation.Req = 0;
  pReq->xdi_dma_descriptor_operation.Rc = IDI_SYNC_REQ_DMA_DESCRIPTOR_OPERATION;

  pReq->xdi_dma_descriptor_operation.info.operation =     IDI_SYNC_REQ_DMA_DESCRIPTOR_ALLOC;
  pReq->xdi_dma_descriptor_operation.info.descriptor_number  = -1;
  pReq->xdi_dma_descriptor_operation.info.descriptor_address = NULL;
  pReq->xdi_dma_descriptor_operation.info.descriptor_magic   = 0;

  e.user[0] = plci->adapter->Id - 1;
  plci->adapter->request((ENTITY*)pReq);

  if (!pReq->xdi_dma_descriptor_operation.info.operation &&
      (pReq->xdi_dma_descriptor_operation.info.descriptor_number >= 0) &&
      pReq->xdi_dma_descriptor_operation.info.descriptor_magic) {
    *dma_magic = pReq->xdi_dma_descriptor_operation.info.descriptor_magic;
    dbug(3,dprintf("dma_alloc, a:%d (%d-%08x)",
         plci->adapter->Id,
         pReq->xdi_dma_descriptor_operation.info.descriptor_number,
         *dma_magic));
    return (pReq->xdi_dma_descriptor_operation.info.descriptor_number);
  } else {
    dbug(1,dprintf("dma_alloc failed"));
    return (-1);
  }
}