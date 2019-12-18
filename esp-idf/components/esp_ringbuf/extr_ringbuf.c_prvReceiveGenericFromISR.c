#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int uxRingbufferFlags; scalar_t__ xItemsWaiting; int /*<<< orphan*/  mux; void* (* pvGetItem ) (TYPE_1__*,scalar_t__*,size_t,size_t*) ;} ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portENTER_CRITICAL_ISR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL_ISR (int /*<<< orphan*/ *) ; 
 scalar_t__ prvCheckItemAvail (TYPE_1__*) ; 
 int rbALLOW_SPLIT_FLAG ; 
 int rbBYTE_BUFFER_FLAG ; 
 int /*<<< orphan*/  rbGET_RX_SEM_HANDLE (TYPE_1__*) ; 
 void* stub1 (TYPE_1__*,scalar_t__*,size_t,size_t*) ; 
 void* stub2 (TYPE_1__*,scalar_t__*,size_t,size_t*) ; 
 void* stub3 (TYPE_1__*,scalar_t__*,size_t,size_t*) ; 
 int /*<<< orphan*/  xSemaphoreGiveFromISR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BaseType_t prvReceiveGenericFromISR(Ringbuffer_t *pxRingbuffer,
                                           void **pvItem1,
                                           void **pvItem2,
                                           size_t *xItemSize1,
                                           size_t *xItemSize2,
                                           size_t xMaxSize)
{
    BaseType_t xReturn = pdFALSE;
    BaseType_t xReturnSemaphore = pdFALSE;

    portENTER_CRITICAL_ISR(&pxRingbuffer->mux);
    if(prvCheckItemAvail(pxRingbuffer) == pdTRUE) {
        BaseType_t xIsSplit;
        if (pxRingbuffer->uxRingbufferFlags & rbBYTE_BUFFER_FLAG) {
            //Second argument (pxIsSplit) is unused for byte buffers
            *pvItem1 = pxRingbuffer->pvGetItem(pxRingbuffer, NULL, xMaxSize, xItemSize1);
        } else {
            //Third argument (xMaxSize) is unused for no-split/allow-split buffers
            *pvItem1 = pxRingbuffer->pvGetItem(pxRingbuffer, &xIsSplit, 0, xItemSize1);
        }
        //Check for item split if configured to do so
        if ((pxRingbuffer->uxRingbufferFlags & rbALLOW_SPLIT_FLAG) && pvItem2 != NULL && xItemSize2 != NULL) {
            if (xIsSplit == pdTRUE) {
                *pvItem2 = pxRingbuffer->pvGetItem(pxRingbuffer, &xIsSplit, 0, xItemSize2);
                configASSERT(*pvItem2 < *pvItem1);  //Check wrap around has occurred
                configASSERT(xIsSplit == pdFALSE);  //Second part should not have wrapped flag
            } else {
                *pvItem2 = NULL;
            }
        }
        xReturn = pdTRUE;
        if (pxRingbuffer->xItemsWaiting > 0) {
            xReturnSemaphore = pdTRUE;
        }
    }
    portEXIT_CRITICAL_ISR(&pxRingbuffer->mux);

    if (xReturnSemaphore == pdTRUE) {
        xSemaphoreGiveFromISR(rbGET_RX_SEM_HANDLE(pxRingbuffer), NULL);  //Give semaphore back so other tasks can retrieve
    }
    return xReturn;
}