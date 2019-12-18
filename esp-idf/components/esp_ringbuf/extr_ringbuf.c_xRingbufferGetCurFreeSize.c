#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t (* xGetCurMaxSize ) (TYPE_1__*) ;int /*<<< orphan*/  mux; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t stub1 (TYPE_1__*) ; 

size_t xRingbufferGetCurFreeSize(RingbufHandle_t xRingbuffer)
{
    Ringbuffer_t *pxRingbuffer = (Ringbuffer_t *)xRingbuffer;
    configASSERT(pxRingbuffer);

    size_t xFreeSize;
    portENTER_CRITICAL(&pxRingbuffer->mux);
    xFreeSize = pxRingbuffer->xGetCurMaxSize(pxRingbuffer);
    portEXIT_CRITICAL(&pxRingbuffer->mux);
    return xFreeSize;
}