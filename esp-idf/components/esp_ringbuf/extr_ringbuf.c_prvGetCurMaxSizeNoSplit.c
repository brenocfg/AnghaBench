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
struct TYPE_3__ {int uxRingbufferFlags; scalar_t__ pucAcquire; scalar_t__ pucFree; size_t pucTail; size_t pucHead; scalar_t__ xMaxItemSize; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int rbBUFFER_FULL_FLAG ; 
 scalar_t__ rbHEADER_SIZE ; 

__attribute__((used)) static size_t prvGetCurMaxSizeNoSplit(Ringbuffer_t *pxRingbuffer)
{
    BaseType_t xFreeSize;
    //Check if buffer is full
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) {
        return 0;
    }
    if (pxRingbuffer->pucAcquire < pxRingbuffer->pucFree) {
        //Free space is contiguous between pucAcquire and pucFree
        xFreeSize = pxRingbuffer->pucFree - pxRingbuffer->pucAcquire;
    } else {
        //Free space wraps around (or overlapped at pucHead), select largest
        //contiguous free space as no-split items require contiguous space
        size_t xSize1 = pxRingbuffer->pucTail - pxRingbuffer->pucAcquire;
        size_t xSize2 = pxRingbuffer->pucFree - pxRingbuffer->pucHead;
        xFreeSize = (xSize1 > xSize2) ? xSize1 : xSize2;
    }

    //No-split ring buffer items need space for a header
    xFreeSize -= rbHEADER_SIZE;
    //Limit free size to be within bounds
    if (xFreeSize > pxRingbuffer->xMaxItemSize) {
        xFreeSize = pxRingbuffer->xMaxItemSize;
    } else if (xFreeSize < 0) {
        //Occurs when free space is less than header size
        xFreeSize = 0;
    }
    return xFreeSize;
}