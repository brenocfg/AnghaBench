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
typedef  scalar_t__ UBaseType_t ;
struct TYPE_3__ {int /*<<< orphan*/  mux; scalar_t__ xItemsWaiting; scalar_t__ pucHead; scalar_t__ pucAcquire; scalar_t__ pucWrite; scalar_t__ pucRead; scalar_t__ pucFree; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

void vRingbufferGetInfo(RingbufHandle_t xRingbuffer,
                        UBaseType_t *uxFree,
                        UBaseType_t *uxRead,
                        UBaseType_t *uxWrite,
                        UBaseType_t *uxAcquire,
                        UBaseType_t *uxItemsWaiting)
{
    Ringbuffer_t *pxRingbuffer = (Ringbuffer_t *)xRingbuffer;
    configASSERT(pxRingbuffer);

    portENTER_CRITICAL(&pxRingbuffer->mux);
    if (uxFree != NULL) {
        *uxFree = (UBaseType_t)(pxRingbuffer->pucFree - pxRingbuffer->pucHead);
    }
    if (uxRead != NULL) {
        *uxRead = (UBaseType_t)(pxRingbuffer->pucRead - pxRingbuffer->pucHead);
    }
    if (uxWrite != NULL) {
        *uxWrite = (UBaseType_t)(pxRingbuffer->pucWrite - pxRingbuffer->pucHead);
    }
    if (uxAcquire != NULL) {
        *uxAcquire = (UBaseType_t)(pxRingbuffer->pucAcquire - pxRingbuffer->pucHead);
    }
    if (uxItemsWaiting != NULL) {
        *uxItemsWaiting = (UBaseType_t)(pxRingbuffer->xItemsWaiting);
    }
    portEXIT_CRITICAL(&pxRingbuffer->mux);
}