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
struct TYPE_3__ {int uxRingbufferFlags; scalar_t__ pucFree; scalar_t__ pucAcquire; scalar_t__ xSize; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int rbBUFFER_FULL_FLAG ; 

__attribute__((used)) static size_t prvGetCurMaxSizeByteBuf(Ringbuffer_t *pxRingbuffer)
{
    BaseType_t xFreeSize;
    //Check if buffer is full
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) {
        return 0;
    }

    /*
     * Return whatever space is available depending on relative positions of the free
     * pointer and Acquire pointer. There is no overhead of headers in this mode
     */
    xFreeSize = pxRingbuffer->pucFree - pxRingbuffer->pucAcquire;
    if (xFreeSize <= 0) {
        xFreeSize += pxRingbuffer->xSize;
    }
    return xFreeSize;
}