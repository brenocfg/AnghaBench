#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ pucAcquire; scalar_t__ pucHead; scalar_t__ pucTail; size_t xItemsWaiting; scalar_t__ pucFree; scalar_t__ pucWrite; int /*<<< orphan*/  uxRingbufferFlags; } ;
typedef  TYPE_1__ Ringbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  memcpy (size_t,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  rbBUFFER_FULL_FLAG ; 

__attribute__((used)) static void prvCopyItemByteBuf(Ringbuffer_t *pxRingbuffer, const uint8_t *pucItem, size_t xItemSize)
{
    //Check arguments and buffer state
    configASSERT(pxRingbuffer->pucAcquire >= pxRingbuffer->pucHead && pxRingbuffer->pucAcquire < pxRingbuffer->pucTail);    //Check acquire pointer is within bounds

    size_t xRemLen = pxRingbuffer->pucTail - pxRingbuffer->pucAcquire;    //Length from pucAcquire until end of buffer
    if (xRemLen < xItemSize) {
        //Copy as much as possible into remaining length
        memcpy(pxRingbuffer->pucAcquire, pucItem, xRemLen);
        pxRingbuffer->xItemsWaiting += xRemLen;
        //Update item arguments to account for data already written
        pucItem += xRemLen;
        xItemSize -= xRemLen;
        pxRingbuffer->pucAcquire = pxRingbuffer->pucHead;     //Reset acquire pointer to start of buffer
    }
    //Copy all or remaining portion of the item
    memcpy(pxRingbuffer->pucAcquire, pucItem, xItemSize);
    pxRingbuffer->xItemsWaiting += xItemSize;
    pxRingbuffer->pucAcquire += xItemSize;

    //Wrap around pucAcquire if it reaches the end
    if (pxRingbuffer->pucAcquire == pxRingbuffer->pucTail) {
        pxRingbuffer->pucAcquire = pxRingbuffer->pucHead;
    }
    //Check if buffer is full
    if (pxRingbuffer->pucAcquire == pxRingbuffer->pucFree) {
        pxRingbuffer->uxRingbufferFlags |= rbBUFFER_FULL_FLAG;      //Mark the buffer as full to avoid confusion with an empty buffer
    }

    //Currently, acquiring memory is not supported in byte mode. pucWrite tracks the pucAcquire.
    pxRingbuffer->pucWrite = pxRingbuffer->pucAcquire;
}