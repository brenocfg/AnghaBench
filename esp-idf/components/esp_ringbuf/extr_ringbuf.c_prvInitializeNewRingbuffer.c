#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t xSize; int xMaxItemSize; int /*<<< orphan*/  mux; int /*<<< orphan*/  xGetCurMaxSize; void* vReturnItem; void* pvGetItem; int /*<<< orphan*/  vCopyItem; void* xCheckItemFits; int /*<<< orphan*/  uxRingbufferFlags; scalar_t__ xItemsWaiting; int /*<<< orphan*/ * pucAcquire; int /*<<< orphan*/ * pucWrite; int /*<<< orphan*/ * pucRead; int /*<<< orphan*/ * pucFree; int /*<<< orphan*/ * pucTail; int /*<<< orphan*/ * pucHead; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ RingbufferType_t ;
typedef  int /*<<< orphan*/  ItemHeader_t ;

/* Variables and functions */
 scalar_t__ RINGBUF_TYPE_ALLOWSPLIT ; 
 scalar_t__ RINGBUF_TYPE_NOSPLIT ; 
 void* prvCheckItemFitsByteBuffer ; 
 void* prvCheckItemFitsDefault ; 
 int /*<<< orphan*/  prvCopyItemAllowSplit ; 
 int /*<<< orphan*/  prvCopyItemByteBuf ; 
 int /*<<< orphan*/  prvCopyItemNoSplit ; 
 int /*<<< orphan*/  prvGetCurMaxSizeAllowSplit ; 
 int /*<<< orphan*/  prvGetCurMaxSizeByteBuf ; 
 int /*<<< orphan*/  prvGetCurMaxSizeNoSplit ; 
 void* prvGetItemByteBuf ; 
 void* prvGetItemDefault ; 
 void* prvReturnItemByteBuf ; 
 void* prvReturnItemDefault ; 
 int rbALIGN_SIZE (int) ; 
 int /*<<< orphan*/  rbALLOW_SPLIT_FLAG ; 
 int /*<<< orphan*/  rbBYTE_BUFFER_FLAG ; 
 int /*<<< orphan*/  rbGET_TX_SEM_HANDLE (TYPE_1__*) ; 
 int rbHEADER_SIZE ; 
 int /*<<< orphan*/  vPortCPUInitializeMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prvInitializeNewRingbuffer(size_t xBufferSize,
                                       RingbufferType_t xBufferType,
                                       Ringbuffer_t *pxNewRingbuffer,
                                       uint8_t *pucRingbufferStorage)
{
    //Initialize values
    pxNewRingbuffer->xSize = xBufferSize;
    pxNewRingbuffer->pucHead = pucRingbufferStorage;
    pxNewRingbuffer->pucTail = pucRingbufferStorage + xBufferSize;
    pxNewRingbuffer->pucFree = pucRingbufferStorage;
    pxNewRingbuffer->pucRead = pucRingbufferStorage;
    pxNewRingbuffer->pucWrite = pucRingbufferStorage;
    pxNewRingbuffer->pucAcquire = pucRingbufferStorage;
    pxNewRingbuffer->xItemsWaiting = 0;
    pxNewRingbuffer->uxRingbufferFlags = 0;

    //Initialize type dependent values and function pointers
    if (xBufferType == RINGBUF_TYPE_NOSPLIT) {
        pxNewRingbuffer->xCheckItemFits = prvCheckItemFitsDefault;
        pxNewRingbuffer->vCopyItem = prvCopyItemNoSplit;
        pxNewRingbuffer->pvGetItem = prvGetItemDefault;
        pxNewRingbuffer->vReturnItem = prvReturnItemDefault;
        /*
         * Worst case scenario is when the read/write/acquire/free pointers are all
         * pointing to the halfway point of the buffer.
         */
        pxNewRingbuffer->xMaxItemSize = rbALIGN_SIZE(pxNewRingbuffer->xSize / 2) - rbHEADER_SIZE;
        pxNewRingbuffer->xGetCurMaxSize = prvGetCurMaxSizeNoSplit;
    } else if (xBufferType == RINGBUF_TYPE_ALLOWSPLIT) {
        pxNewRingbuffer->uxRingbufferFlags |= rbALLOW_SPLIT_FLAG;
        pxNewRingbuffer->xCheckItemFits = prvCheckItemFitsDefault;
        pxNewRingbuffer->vCopyItem = prvCopyItemAllowSplit;
        pxNewRingbuffer->pvGetItem = prvGetItemDefault;
        pxNewRingbuffer->vReturnItem = prvReturnItemDefault;
        //Worst case an item is split into two, incurring two headers of overhead
        pxNewRingbuffer->xMaxItemSize = pxNewRingbuffer->xSize - (sizeof(ItemHeader_t) * 2);
        pxNewRingbuffer->xGetCurMaxSize = prvGetCurMaxSizeAllowSplit;
    } else { //Byte Buffer
        pxNewRingbuffer->uxRingbufferFlags |= rbBYTE_BUFFER_FLAG;
        pxNewRingbuffer->xCheckItemFits = prvCheckItemFitsByteBuffer;
        pxNewRingbuffer->vCopyItem = prvCopyItemByteBuf;
        pxNewRingbuffer->pvGetItem = prvGetItemByteBuf;
        pxNewRingbuffer->vReturnItem = prvReturnItemByteBuf;
        //Byte buffers do not incur any overhead
        pxNewRingbuffer->xMaxItemSize = pxNewRingbuffer->xSize;
        pxNewRingbuffer->xGetCurMaxSize = prvGetCurMaxSizeByteBuf;
    }
    xSemaphoreGive(rbGET_TX_SEM_HANDLE(pxNewRingbuffer));
    vPortCPUInitializeMutex(&pxNewRingbuffer->mux);
}