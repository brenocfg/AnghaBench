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
struct TYPE_3__ {scalar_t__ xItemsWaiting; int uxRingbufferFlags; int /*<<< orphan*/ * pucRead; int /*<<< orphan*/ * pucWrite; int /*<<< orphan*/ * pucHead; int /*<<< orphan*/ * pucTail; int /*<<< orphan*/ * pucFree; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int rbBUFFER_FULL_FLAG ; 

__attribute__((used)) static void *prvGetItemByteBuf(Ringbuffer_t *pxRingbuffer,
                               BaseType_t *pxUnusedParam,
                               size_t xMaxSize,
                               size_t *pxItemSize)
{
    //Check arguments and buffer state
    configASSERT((pxRingbuffer->xItemsWaiting > 0) && ((pxRingbuffer->pucRead != pxRingbuffer->pucWrite) || (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG)));   //Check there are items to be read
    configASSERT(pxRingbuffer->pucRead >= pxRingbuffer->pucHead && pxRingbuffer->pucRead < pxRingbuffer->pucTail);    //Check read pointer is within bounds
    configASSERT(pxRingbuffer->pucRead == pxRingbuffer->pucFree);

    uint8_t *ret = pxRingbuffer->pucRead;
    if ((pxRingbuffer->pucRead > pxRingbuffer->pucWrite) || (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG)) {     //Available data wraps around
        //Return contiguous piece from read pointer until buffer tail, or xMaxSize
        if (xMaxSize == 0 || pxRingbuffer->pucTail - pxRingbuffer->pucRead <= xMaxSize) {
            //All contiguous data from read pointer to tail
            *pxItemSize = pxRingbuffer->pucTail - pxRingbuffer->pucRead;
            pxRingbuffer->xItemsWaiting -= pxRingbuffer->pucTail - pxRingbuffer->pucRead;
            pxRingbuffer->pucRead = pxRingbuffer->pucHead;  //Wrap around read pointer
        } else {
            //Return xMaxSize amount of data
            *pxItemSize = xMaxSize;
            pxRingbuffer->xItemsWaiting -= xMaxSize;
            pxRingbuffer->pucRead += xMaxSize;  //Advance read pointer past retrieved data
        }
    } else {    //Available data is contiguous between read and write pointer
        if (xMaxSize == 0 || pxRingbuffer->pucWrite - pxRingbuffer->pucRead <= xMaxSize) {
            //Return all contiguous data from read to write pointer
            *pxItemSize = pxRingbuffer->pucWrite - pxRingbuffer->pucRead;
            pxRingbuffer->xItemsWaiting -= pxRingbuffer->pucWrite - pxRingbuffer->pucRead;
            pxRingbuffer->pucRead = pxRingbuffer->pucWrite;
        } else {
            //Return xMaxSize data from read pointer
            *pxItemSize = xMaxSize;
            pxRingbuffer->xItemsWaiting -= xMaxSize;
            pxRingbuffer->pucRead += xMaxSize;  //Advance read pointer past retrieved data

        }
    }
    return (void *)ret;
}