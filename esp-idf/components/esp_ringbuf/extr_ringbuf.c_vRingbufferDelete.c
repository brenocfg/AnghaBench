#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int uxRingbufferFlags; struct TYPE_6__* pucHead; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int rbBUFFER_STATIC_FLAG ; 
 int /*<<< orphan*/  rbGET_RX_SEM_HANDLE (TYPE_1__*) ; 
 int /*<<< orphan*/  rbGET_TX_SEM_HANDLE (TYPE_1__*) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 

void vRingbufferDelete(RingbufHandle_t xRingbuffer)
{
    Ringbuffer_t *pxRingbuffer = (Ringbuffer_t *)xRingbuffer;
    configASSERT(pxRingbuffer);

    vSemaphoreDelete(rbGET_TX_SEM_HANDLE(pxRingbuffer));
    vSemaphoreDelete(rbGET_RX_SEM_HANDLE(pxRingbuffer));

#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_STATIC_FLAG) {
        //Ring buffer was statically allocated, no need to free
        return;
    }
#endif
    free(pxRingbuffer->pucHead);
    free(pxRingbuffer);
}