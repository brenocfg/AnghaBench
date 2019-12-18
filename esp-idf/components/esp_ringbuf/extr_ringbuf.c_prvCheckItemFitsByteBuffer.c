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
struct TYPE_3__ {scalar_t__ pucAcquire; scalar_t__ pucHead; scalar_t__ pucTail; scalar_t__ pucFree; int uxRingbufferFlags; size_t xSize; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  pdTRUE ; 
 int rbBUFFER_FULL_FLAG ; 

__attribute__((used)) static BaseType_t prvCheckItemFitsByteBuffer( Ringbuffer_t *pxRingbuffer, size_t xItemSize)
{
    //Check arguments and buffer state
    configASSERT(pxRingbuffer->pucAcquire >= pxRingbuffer->pucHead && pxRingbuffer->pucAcquire < pxRingbuffer->pucTail);    //Check acquire pointer is within bounds

    if (pxRingbuffer->pucAcquire == pxRingbuffer->pucFree) {
        //Buffer is either complete empty or completely full
        return (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) ? pdFALSE : pdTRUE;
    }
    if (pxRingbuffer->pucFree > pxRingbuffer->pucAcquire) {
        //Free space does not wrap around
        return (xItemSize <= pxRingbuffer->pucFree - pxRingbuffer->pucAcquire) ? pdTRUE : pdFALSE;
    }
    //Free space wraps around
    return (xItemSize <= pxRingbuffer->xSize - (pxRingbuffer->pucAcquire - pxRingbuffer->pucFree)) ? pdTRUE : pdFALSE;
}