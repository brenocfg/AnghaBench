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
struct TYPE_4__ {int /*<<< orphan*/  uxRingbufferFlags; int /*<<< orphan*/ * pucFree; int /*<<< orphan*/ * pucAcquire; int /*<<< orphan*/ * pucHead; int /*<<< orphan*/ * pucTail; } ;
typedef  TYPE_1__ Ringbuffer_t ;
typedef  TYPE_2__ ItemHeader_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 size_t rbALIGN_SIZE (size_t) ; 
 int /*<<< orphan*/  rbBUFFER_FULL_FLAG ; 
 int rbCHECK_ALIGNED (int /*<<< orphan*/ *) ; 
 size_t rbHEADER_SIZE ; 
 scalar_t__ rbITEM_DUMMY_DATA_FLAG ; 

__attribute__((used)) static uint8_t* prvAcquireItemNoSplit(Ringbuffer_t *pxRingbuffer, size_t xItemSize)
{
    //Check arguments and buffer state
    size_t xAlignedItemSize = rbALIGN_SIZE(xItemSize);                  //Rounded up aligned item size
    size_t xRemLen = pxRingbuffer->pucTail - pxRingbuffer->pucAcquire;    //Length from pucAcquire until end of buffer
    configASSERT(rbCHECK_ALIGNED(pxRingbuffer->pucAcquire));              //pucAcquire is always aligned in no-split ring buffers
    configASSERT(pxRingbuffer->pucAcquire >= pxRingbuffer->pucHead && pxRingbuffer->pucAcquire < pxRingbuffer->pucTail);    //Check write pointer is within bounds
    configASSERT(xRemLen >= rbHEADER_SIZE);                             //Remaining length must be able to at least fit an item header

    //If remaining length can't fit item, set as dummy data and wrap around
    if (xRemLen < xAlignedItemSize + rbHEADER_SIZE) {
        ItemHeader_t *pxDummy = (ItemHeader_t *)pxRingbuffer->pucAcquire;
        pxDummy->uxItemFlags = rbITEM_DUMMY_DATA_FLAG;      //Set remaining length as dummy data
        pxDummy->xItemLen = 0;                              //Dummy data should have no length
        pxRingbuffer->pucAcquire = pxRingbuffer->pucHead;     //Reset acquire pointer to wrap around
    }

    //Item should be guaranteed to fit at this point. Set item header and copy data
    ItemHeader_t *pxHeader = (ItemHeader_t *)pxRingbuffer->pucAcquire;
    pxHeader->xItemLen = xItemSize;
    pxHeader->uxItemFlags = 0;

    //hold the buffer address without touching pucWrite
    uint8_t* item_address = pxRingbuffer->pucAcquire + rbHEADER_SIZE;
    pxRingbuffer->pucAcquire += rbHEADER_SIZE + xAlignedItemSize;    //Advance pucAcquire past header and the item to next aligned address

    //After the allocation, add some padding after the buffer and correct the flags
    //If current remaining length can't fit a header, wrap around write pointer
    if (pxRingbuffer->pucTail - pxRingbuffer->pucAcquire < rbHEADER_SIZE) {
        pxRingbuffer->pucAcquire = pxRingbuffer->pucHead;   //Wrap around pucAcquire
    }
    //Check if buffer is full
    if (pxRingbuffer->pucAcquire == pxRingbuffer->pucFree) {
        //Mark the buffer as full to distinguish with an empty buffer
        pxRingbuffer->uxRingbufferFlags |= rbBUFFER_FULL_FLAG;
    }
    return item_address;
}