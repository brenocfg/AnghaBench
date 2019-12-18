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
struct TYPE_3__ {int uxRingbufferFlags; size_t pucFree; size_t pucAcquire; size_t xSize; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  size_t BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int rbBUFFER_FULL_FLAG ; 

__attribute__((used)) static size_t prvGetFreeSize(Ringbuffer_t *pxRingbuffer)
{
    size_t xReturn;
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) {
        xReturn =  0;
    } else {
        BaseType_t xFreeSize = pxRingbuffer->pucFree - pxRingbuffer->pucAcquire;
        //Check if xFreeSize has underflowed
        if (xFreeSize <= 0) {
            xFreeSize += pxRingbuffer->xSize;
        }
        xReturn = xFreeSize;
    }
    configASSERT(xReturn <= pxRingbuffer->xSize);
    return xReturn;
}