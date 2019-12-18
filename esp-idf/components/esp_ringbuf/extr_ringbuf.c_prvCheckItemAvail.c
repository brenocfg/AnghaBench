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
struct TYPE_3__ {int uxRingbufferFlags; scalar_t__ pucRead; scalar_t__ pucFree; scalar_t__ xItemsWaiting; scalar_t__ pucWrite; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  pdTRUE ; 
 int rbBUFFER_FULL_FLAG ; 
 int rbBYTE_BUFFER_FLAG ; 

__attribute__((used)) static BaseType_t prvCheckItemAvail(Ringbuffer_t *pxRingbuffer)
{
    if ((pxRingbuffer->uxRingbufferFlags & rbBYTE_BUFFER_FLAG) && pxRingbuffer->pucRead != pxRingbuffer->pucFree) {
        return pdFALSE;     //Byte buffers do not allow multiple retrievals before return
    }
    if ((pxRingbuffer->xItemsWaiting > 0) && ((pxRingbuffer->pucRead != pxRingbuffer->pucWrite) || (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG))) {
        return pdTRUE;      //Items/data available for retrieval
    } else {
        return pdFALSE;     //No items/data available for retrieval
    }
}