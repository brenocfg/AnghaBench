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
struct TYPE_4__ {int xSize; int pucRead; int pucHead; int pucFree; int pucWrite; int pucAcquire; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  scalar_t__ RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 int prvGetFreeSize (TYPE_1__*) ; 

void xRingbufferPrintInfo(RingbufHandle_t xRingbuffer)
{
    Ringbuffer_t *pxRingbuffer = (Ringbuffer_t *)xRingbuffer;
    configASSERT(pxRingbuffer);
    printf("Rb size:%d\tfree: %d\trptr: %d\tfreeptr: %d\twptr: %d, aptr: %d\n",
           pxRingbuffer->xSize, prvGetFreeSize(pxRingbuffer),
           pxRingbuffer->pucRead - pxRingbuffer->pucHead,
           pxRingbuffer->pucFree - pxRingbuffer->pucHead,
           pxRingbuffer->pucWrite - pxRingbuffer->pucHead,
           pxRingbuffer->pucAcquire - pxRingbuffer->pucHead);
}