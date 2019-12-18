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
struct TYPE_3__ {int uxRingbufferFlags; scalar_t__ pucAcquire; scalar_t__ pucHead; scalar_t__ pucFree; scalar_t__ xSize; scalar_t__ pucTail; scalar_t__ xMaxItemSize; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int rbBUFFER_FULL_FLAG ; 
 int rbHEADER_SIZE ; 

__attribute__((used)) static size_t prvGetCurMaxSizeAllowSplit(Ringbuffer_t *pxRingbuffer)
{
    BaseType_t xFreeSize;
    //Check if buffer is full
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) {
        return 0;
    }
    if (pxRingbuffer->pucAcquire == pxRingbuffer->pucHead && pxRingbuffer->pucFree == pxRingbuffer->pucHead) {
        //Check for special case where pucAcquire and pucFree are both at pucHead
        xFreeSize = pxRingbuffer->xSize - rbHEADER_SIZE;
    } else if (pxRingbuffer->pucAcquire < pxRingbuffer->pucFree) {
        //Free space is contiguous between pucAcquire and pucFree, requires single header
        xFreeSize = (pxRingbuffer->pucFree - pxRingbuffer->pucAcquire) - rbHEADER_SIZE;
    } else {
        //Free space wraps around, requires two headers
        xFreeSize = (pxRingbuffer->pucFree - pxRingbuffer->pucHead) +
                    (pxRingbuffer->pucTail - pxRingbuffer->pucAcquire) -
                    (rbHEADER_SIZE * 2);
    }

    //Limit free size to be within bounds
    if (xFreeSize > pxRingbuffer->xMaxItemSize) {
        xFreeSize = pxRingbuffer->xMaxItemSize;
    } else if (xFreeSize < 0) {
        xFreeSize = 0;
    }
    return xFreeSize;
}