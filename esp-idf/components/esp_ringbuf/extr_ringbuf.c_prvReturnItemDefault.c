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
struct TYPE_5__ {scalar_t__ xItemLen; int uxItemFlags; } ;
struct TYPE_4__ {scalar_t__ xMaxItemSize; int xSize; int uxRingbufferFlags; int /*<<< orphan*/ * pucRead; int /*<<< orphan*/ * pucFree; int /*<<< orphan*/ * pucAcquire; int /*<<< orphan*/ * pucHead; int /*<<< orphan*/ * pucTail; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  TYPE_2__ ItemHeader_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 size_t rbALIGN_SIZE (scalar_t__) ; 
 int rbBUFFER_FULL_FLAG ; 
 int rbCHECK_ALIGNED (int /*<<< orphan*/ *) ; 
 int rbHEADER_SIZE ; 
 int rbITEM_DUMMY_DATA_FLAG ; 
 int rbITEM_FREE_FLAG ; 
 int rbITEM_SPLIT_FLAG ; 

__attribute__((used)) static void prvReturnItemDefault(Ringbuffer_t *pxRingbuffer, uint8_t *pucItem)
{
    //Check arguments and buffer state
    configASSERT(rbCHECK_ALIGNED(pucItem));
    configASSERT(pucItem >= pxRingbuffer->pucHead);
    configASSERT(pucItem <= pxRingbuffer->pucTail);     //Inclusive of pucTail in the case of zero length item at the very end

    //Get and check header of the item
    ItemHeader_t *pxCurHeader = (ItemHeader_t *)(pucItem - rbHEADER_SIZE);
    configASSERT(pxCurHeader->xItemLen <= pxRingbuffer->xMaxItemSize);
    configASSERT((pxCurHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG) == 0); //Dummy items should never have been read
    configASSERT((pxCurHeader->uxItemFlags & rbITEM_FREE_FLAG) == 0);       //Indicates item has already been returned before
    pxCurHeader->uxItemFlags &= ~rbITEM_SPLIT_FLAG;                         //Clear wrap flag if set (not strictly necessary)
    pxCurHeader->uxItemFlags |= rbITEM_FREE_FLAG;                           //Mark as free

    /*
     * Items might not be returned in the order they were retrieved. Move the free pointer
     * up to the next item that has not been marked as free (by free flag) or up
     * till the read pointer. When advancing the free pointer, items that have already been
     * freed or items with dummy data should be skipped over
     */
    pxCurHeader = (ItemHeader_t *)pxRingbuffer->pucFree;
    //Skip over Items that have already been freed or are dummy items
    while (((pxCurHeader->uxItemFlags & rbITEM_FREE_FLAG) || (pxCurHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG)) && pxRingbuffer->pucFree != pxRingbuffer->pucRead) {
        if (pxCurHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG) {
            pxCurHeader->uxItemFlags |= rbITEM_FREE_FLAG;   //Mark as freed (not strictly necessary but adds redundancy)
            pxRingbuffer->pucFree = pxRingbuffer->pucHead;    //Wrap around due to dummy data
        } else {
            //Item with data that has already been freed, advance free pointer past this item
            size_t xAlignedItemSize = rbALIGN_SIZE(pxCurHeader->xItemLen);
            pxRingbuffer->pucFree += xAlignedItemSize + rbHEADER_SIZE;
            //Redundancy check to ensure free pointer has not overshot buffer bounds
            configASSERT(pxRingbuffer->pucFree <= pxRingbuffer->pucHead + pxRingbuffer->xSize);
        }
        //Check if pucRead requires wrap around
        if ((pxRingbuffer->pucTail - pxRingbuffer->pucFree) < rbHEADER_SIZE) {
            pxRingbuffer->pucFree = pxRingbuffer->pucHead;
        }
        pxCurHeader = (ItemHeader_t *)pxRingbuffer->pucFree;      //Update header to point to item
    }

    //Check if the buffer full flag should be reset
    if (pxRingbuffer->uxRingbufferFlags & rbBUFFER_FULL_FLAG) {
        if (pxRingbuffer->pucFree != pxRingbuffer->pucAcquire) {
            pxRingbuffer->uxRingbufferFlags &= ~rbBUFFER_FULL_FLAG;
        } else if (pxRingbuffer->pucFree == pxRingbuffer->pucAcquire && pxRingbuffer->pucFree == pxRingbuffer->pucRead) {
            //Special case where a full buffer is completely freed in one go
            pxRingbuffer->uxRingbufferFlags &= ~rbBUFFER_FULL_FLAG;
        }
    }
}