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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int uxRingbufferFlags; int /*<<< orphan*/  pucRead; int /*<<< orphan*/  pucFree; int /*<<< orphan*/ * pucTail; int /*<<< orphan*/ * pucHead; } ;
typedef  TYPE_1__ Ringbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int rbBUFFER_FULL_FLAG ; 

__attribute__((used)) static void prvReturnItemByteBuf(Ringbuffer_t *pxRingbuffer, uint8_t *pucItem)
{
    //Check pointer points to address inside buffer
    configASSERT((uint8_t *)pucItem >= pxRingbuffer->pucHead);
    configASSERT((uint8_t *)pucItem < pxRingbuffer->pucTail);
    //Free the read memory. Simply moves free pointer to read pointer as byte buffers do not allow multiple outstanding reads
    pxRingbuffer->pucFree = pxRingbuffer->pucRead;
    //If buffer was full before, reset full flag as free pointer has moved
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) {
        pxRingbuffer->uxRingbufferFlags &= ~rbBUFFER_FULL_FLAG;
    }
}