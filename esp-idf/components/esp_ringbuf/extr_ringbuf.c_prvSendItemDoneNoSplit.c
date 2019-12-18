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
struct TYPE_4__ {scalar_t__ xMaxItemSize; int xSize; int /*<<< orphan*/ * pucWrite; int /*<<< orphan*/ * pucHead; int /*<<< orphan*/ * pucTail; int /*<<< orphan*/ * pucAcquire; int /*<<< orphan*/  xItemsWaiting; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  TYPE_2__ ItemHeader_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 size_t rbALIGN_SIZE (scalar_t__) ; 
 int rbCHECK_ALIGNED (int /*<<< orphan*/ *) ; 
 int rbHEADER_SIZE ; 
 int rbITEM_DUMMY_DATA_FLAG ; 
 int rbITEM_SPLIT_FLAG ; 
 int rbITEM_WRITTEN_FLAG ; 

__attribute__((used)) static void prvSendItemDoneNoSplit(Ringbuffer_t *pxRingbuffer, uint8_t* pucItem)
{
    //Check arguments and buffer state
    configASSERT(rbCHECK_ALIGNED(pucItem));
    configASSERT(pucItem >= pxRingbuffer->pucHead);
    configASSERT(pucItem <= pxRingbuffer->pucTail);     //Inclusive of pucTail in the case of zero length item at the very end

    //Get and check header of the item
    ItemHeader_t *pxCurHeader = (ItemHeader_t *)(pucItem - rbHEADER_SIZE);
    configASSERT(pxCurHeader->xItemLen <= pxRingbuffer->xMaxItemSize);
    configASSERT((pxCurHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG) == 0); //Dummy items should never have been written
    configASSERT((pxCurHeader->uxItemFlags & rbITEM_WRITTEN_FLAG) == 0);       //Indicates item has already been written before
    pxCurHeader->uxItemFlags &= ~rbITEM_SPLIT_FLAG;                         //Clear wrap flag if set (not strictly necessary)
    pxCurHeader->uxItemFlags |= rbITEM_WRITTEN_FLAG;                           //Mark as written

    pxRingbuffer->xItemsWaiting++;

    /*
     * Items might not be written in the order they were acquired. Move the
     * write pointer up to the next item that has not been marked as written (by
     * written flag) or up till the acquire pointer. When advancing the write
     * pointer, items that have already been written or items with dummy data
     * should be skipped over
     */
    pxCurHeader = (ItemHeader_t *)pxRingbuffer->pucWrite;
    //Skip over Items that have already been written or are dummy items
    while (((pxCurHeader->uxItemFlags & rbITEM_WRITTEN_FLAG) || (pxCurHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG)) && pxRingbuffer->pucWrite != pxRingbuffer->pucAcquire) {
        if (pxCurHeader->uxItemFlags & rbITEM_DUMMY_DATA_FLAG) {
            pxCurHeader->uxItemFlags |= rbITEM_WRITTEN_FLAG;   //Mark as freed (not strictly necessary but adds redundancy)
            pxRingbuffer->pucWrite = pxRingbuffer->pucHead;    //Wrap around due to dummy data
        } else {
            //Item with data that has already been written, advance write pointer past this item
            size_t xAlignedItemSize = rbALIGN_SIZE(pxCurHeader->xItemLen);
            pxRingbuffer->pucWrite += xAlignedItemSize + rbHEADER_SIZE;
            //Redundancy check to ensure write pointer has not overshot buffer bounds
            configASSERT(pxRingbuffer->pucWrite <= pxRingbuffer->pucHead + pxRingbuffer->xSize);
        }
        //Check if pucAcquire requires wrap around
        if ((pxRingbuffer->pucTail - pxRingbuffer->pucWrite) < rbHEADER_SIZE) {
            pxRingbuffer->pucWrite = pxRingbuffer->pucHead;
        }
        pxCurHeader = (ItemHeader_t *)pxRingbuffer->pucWrite;      //Update header to point to item
    }
}