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
struct TYPE_8__ {int /*<<< orphan*/ * xRecvSemHandle; int /*<<< orphan*/ * xTransSemHandle; int /*<<< orphan*/  xRecvSemStatic; int /*<<< orphan*/  xTransSemStatic; } ;
typedef  TYPE_1__ uint8_t ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ RingbufferType_t ;
typedef  int /*<<< orphan*/ * RingbufHandle_t ;

/* Variables and functions */
 scalar_t__ RINGBUF_TYPE_BYTEBUF ; 
 scalar_t__ RINGBUF_TYPE_MAX ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (size_t) ; 
 int /*<<< orphan*/  prvInitializeNewRingbuffer (size_t,scalar_t__,TYPE_1__*,TYPE_1__*) ; 
 size_t rbALIGN_SIZE (size_t) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 void* xSemaphoreCreateBinary () ; 
 int /*<<< orphan*/  xSemaphoreCreateBinaryStatic (int /*<<< orphan*/ *) ; 

RingbufHandle_t xRingbufferCreate(size_t xBufferSize, RingbufferType_t xBufferType)
{
    configASSERT(xBufferSize > 0);
    configASSERT(xBufferType < RINGBUF_TYPE_MAX);

    //Allocate memory
    if (xBufferType != RINGBUF_TYPE_BYTEBUF) {
        xBufferSize = rbALIGN_SIZE(xBufferSize);    //xBufferSize is rounded up for no-split/allow-split buffers
    }
    Ringbuffer_t *pxNewRingbuffer = calloc(1, sizeof(Ringbuffer_t));
    uint8_t *pucRingbufferStorage = malloc(xBufferSize);
    if (pxNewRingbuffer == NULL || pucRingbufferStorage == NULL) {
        goto err;
    }

    //Initialize Semaphores
#if ( configSUPPORT_STATIC_ALLOCATION == 1)
    //We don't use the handles for static semaphores, and xSemaphoreCreateBinaryStatic will never fail thus no need to check static case
    xSemaphoreCreateBinaryStatic(&(pxNewRingbuffer->xTransSemStatic));
    xSemaphoreCreateBinaryStatic(&(pxNewRingbuffer->xRecvSemStatic));
#else
    pxNewRingbuffer->xTransSemHandle = xSemaphoreCreateBinary();
    pxNewRingbuffer->xRecvSemHandle = xSemaphoreCreateBinary();
    if (pxNewRingbuffer->xTransSemHandle == NULL || pxNewRingbuffer->xRecvSemHandle == NULL) {
        if (pxNewRingbuffer->xTransSemHandle != NULL) {
            vSemaphoreDelete(pxNewRingbuffer->xTransSemHandle);
        }
        if (pxNewRingbuffer->xRecvSemHandle != NULL) {
            vSemaphoreDelete(pxNewRingbuffer->xRecvSemHandle);
        }
        goto err;
    }
#endif

    prvInitializeNewRingbuffer(xBufferSize, xBufferType, pxNewRingbuffer, pucRingbufferStorage);
    return (RingbufHandle_t)pxNewRingbuffer;

err:
    //An error has occurred, Free memory and return NULL
    free(pxNewRingbuffer);
    free(pucRingbufferStorage);
    return NULL;
}