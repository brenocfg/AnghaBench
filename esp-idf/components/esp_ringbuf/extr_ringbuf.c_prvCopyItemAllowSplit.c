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
struct TYPE_5__ {size_t xItemLen; scalar_t__ uxItemFlags; } ;
struct TYPE_4__ {size_t pucTail; size_t pucAcquire; scalar_t__ pucHead; scalar_t__ pucFree; scalar_t__ pucWrite; int /*<<< orphan*/  uxRingbufferFlags; int /*<<< orphan*/  xItemsWaiting; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  TYPE_2__ ItemHeader_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 size_t rbALIGN_SIZE (size_t) ; 
 int /*<<< orphan*/  rbBUFFER_FULL_FLAG ; 
 int rbCHECK_ALIGNED (size_t) ; 
 size_t rbHEADER_SIZE ; 
 scalar_t__ rbITEM_DUMMY_DATA_FLAG ; 
 scalar_t__ rbITEM_SPLIT_FLAG ; 

__attribute__((used)) static void prvCopyItemAllowSplit(Ringbuffer_t *pxRingbuffer, const uint8_t *pucItem, size_t xItemSize)
{
    //Check arguments and buffer state
    size_t xAlignedItemSize = rbALIGN_SIZE(xItemSize);                  //Rounded up aligned item size
    size_t xRemLen = pxRingbuffer->pucTail - pxRingbuffer->pucAcquire;    //Length from pucAcquire until end of buffer
    configASSERT(rbCHECK_ALIGNED(pxRingbuffer->pucAcquire));              //pucAcquire is always aligned in split ring buffers
    configASSERT(pxRingbuffer->pucAcquire >= pxRingbuffer->pucHead && pxRingbuffer->pucAcquire < pxRingbuffer->pucTail);    //Check write pointer is within bounds
    configASSERT(xRemLen >= rbHEADER_SIZE);                             //Remaining length must be able to at least fit an item header

    //Split item if necessary
    if (xRemLen < xAlignedItemSize + rbHEADER_SIZE) {
        //Write first part of the item
        ItemHeader_t *pxFirstHeader = (ItemHeader_t *)pxRingbuffer->pucAcquire;
        pxFirstHeader->uxItemFlags = 0;
        pxFirstHeader->xItemLen = xRemLen - rbHEADER_SIZE;  //Fill remaining length with first part
        pxRingbuffer->pucAcquire += rbHEADER_SIZE;            //Advance pucAcquire past header
        xRemLen -= rbHEADER_SIZE;
        if (xRemLen > 0) {
            memcpy(pxRingbuffer->pucAcquire, pucItem, xRemLen);
            pxRingbuffer->xItemsWaiting++;
            //Update item arguments to account for data already copied
            pucItem += xRemLen;
            xItemSize -= xRemLen;
            xAlignedItemSize -= xRemLen;
            pxFirstHeader->uxItemFlags |= rbITEM_SPLIT_FLAG;        //There must be more data
        } else {
            //Remaining length was only large enough to fit header
            pxFirstHeader->uxItemFlags |= rbITEM_DUMMY_DATA_FLAG;   //Item will completely be stored in 2nd part
        }
        pxRingbuffer->pucAcquire = pxRingbuffer->pucHead;             //Reset acquire pointer to start of buffer
    }

    //Item (whole or second part) should be guaranteed to fit at this point
    ItemHeader_t *pxSecondHeader = (ItemHeader_t *)pxRingbuffer->pucAcquire;
    pxSecondHeader->xItemLen = xItemSize;
    pxSecondHeader->uxItemFlags = 0;
    pxRingbuffer->pucAcquire += rbHEADER_SIZE;     //Advance acquire pointer past header
    memcpy(pxRingbuffer->pucAcquire, pucItem, xItemSize);
    pxRingbuffer->xItemsWaiting++;
    pxRingbuffer->pucAcquire += xAlignedItemSize;  //Advance pucAcquire past item to next aligned address

    //If current remaining length can't fit a header, wrap around write pointer
    if (pxRingbuffer->pucTail - pxRingbuffer->pucAcquire < rbHEADER_SIZE) {
        pxRingbuffer->pucAcquire = pxRingbuffer->pucHead;   //Wrap around pucAcquire
    }
    //Check if buffer is full
    if (pxRingbuffer->pucAcquire == pxRingbuffer->pucFree) {
        //Mark the buffer as full to distinguish with an empty buffer
        pxRingbuffer->uxRingbufferFlags |= rbBUFFER_FULL_FLAG;
    }

    //currently the Split mode is not supported, pucWrite tracks the pucAcquire
    pxRingbuffer->pucWrite = pxRingbuffer->pucAcquire;
}