#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t xItemLen; int uxItemFlags; } ;
struct TYPE_4__ {scalar_t__ xItemsWaiting; int uxRingbufferFlags; size_t xMaxItemSize; int /*<<< orphan*/ * pucHead; int /*<<< orphan*/ * pucRead; int /*<<< orphan*/ * pucTail; int /*<<< orphan*/ * pucWrite; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  TYPE_2__ ItemHeader_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  pdTRUE ; 
 int rbALIGN_SIZE (size_t) ; 
 int rbBUFFER_FULL_FLAG ; 
 int rbCHECK_ALIGNED (int /*<<< orphan*/ *) ; 
 int rbHEADER_SIZE ; 
 int rbITEM_DUMMY_DATA_FLAG ; 
 int rbITEM_SPLIT_FLAG ; 

__attribute__((used)) static void *prvGetItemDefault(Ringbuffer_t *pxRingbuffer,
                               BaseType_t *pxIsSplit,
                               size_t xUnusedParam,
                               size_t *pxItemSize)
{
    //Check arguments and buffer state
    ItemHeader_t *pxHeader = (ItemHeader_t *)pxRingbuffer->pucRead;
    configASSERT(pxIsSplit != NULL);
    configASSERT((pxRingbuffer->xItemsWaiting > 0) && ((pxRingbuffer->pucRead != pxRingbuffer->pucWrite) || (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG)));   //Check there are items to be read
    configASSERT(rbCHECK_ALIGNED(pxRingbuffer->pucRead));           //pucRead is always aligned in split ring buffers
    configASSERT(pxRingbuffer->pucRead >= pxRingbuffer->pucHead && pxRingbuffer->pucRead < pxRingbuffer->pucTail);      //Check read pointer is within bounds
    configASSERT((pxHeader->xItemLen <= pxRingbuffer->xMaxItemSize) || (pxHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG));

    uint8_t *pcReturn;
    //Wrap around if dummy data (dummy data indicates wrap around in no-split buffers)
    if (pxHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG) {
        pxRingbuffer->pucRead = pxRingbuffer->pucHead;
        //Check for errors with the next item
        pxHeader = (ItemHeader_t *)pxRingbuffer->pucRead;
        configASSERT(pxHeader->xItemLen <= pxRingbuffer->xMaxItemSize);
    }
    pcReturn = pxRingbuffer->pucRead + rbHEADER_SIZE;    //Get pointer to part of item containing data (point past the header)
    if (pxHeader->xItemLen == 0) {
        //Inclusive of pucTail for special case where item of zero length just fits at the end of the buffer
        configASSERT(pcReturn >= pxRingbuffer->pucHead && pcReturn <= pxRingbuffer->pucTail);
    } else {
        //Exclusive of pucTali if length is larger than zero, pcReturn should never point to pucTail
        configASSERT(pcReturn >= pxRingbuffer->pucHead && pcReturn < pxRingbuffer->pucTail);
    }
    *pxItemSize = pxHeader->xItemLen;   //Get length of item
    pxRingbuffer->xItemsWaiting --;     //Update item count
    *pxIsSplit = (pxHeader->uxItemFlags & rbITEM_SPLIT_FLAG) ? pdTRUE : pdFALSE;

    pxRingbuffer->pucRead += rbHEADER_SIZE + rbALIGN_SIZE(pxHeader->xItemLen);   //Update pucRead
    //Check if pucRead requires wrap around
    if ((pxRingbuffer->pucTail - pxRingbuffer->pucRead) < rbHEADER_SIZE) {
        pxRingbuffer->pucRead = pxRingbuffer->pucHead;
    }
    return (void *)pcReturn;
}