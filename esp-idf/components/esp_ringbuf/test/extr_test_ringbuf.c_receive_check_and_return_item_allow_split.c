#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ const uint8_t ;
typedef  int /*<<< orphan*/  TickType_t ;
typedef  int /*<<< orphan*/  RingbufHandle_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_MESSAGE (int,char*) ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vRingbufferReturnItemFromISR (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ xRingbufferReceiveSplit (int /*<<< orphan*/ ,void**,void**,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ xRingbufferReceiveSplitFromISR (int /*<<< orphan*/ ,void**,void**,size_t*,size_t*) ; 

__attribute__((used)) static void receive_check_and_return_item_allow_split(RingbufHandle_t handle, const uint8_t *expected_data, size_t expected_size, TickType_t ticks_to_wait, bool in_isr)
{
    //Receive item
    size_t item_size1, item_size2;
    uint8_t *item1, *item2;
    BaseType_t ret;
    if (in_isr) {
        ret = xRingbufferReceiveSplitFromISR(handle, (void**)&item1, (void **)&item2, &item_size1, &item_size2);
    } else {
        ret = xRingbufferReceiveSplit(handle, (void**)&item1, (void **)&item2, &item_size1, &item_size2, ticks_to_wait);
    }
    //= xRingbufferReceiveSplit(handle, (void**)&item1, (void **)&item2, &item_size1, &item_size2, ticks_to_wait);
    TEST_ASSERT_MESSAGE(ret == pdTRUE, "Failed to receive item");
    TEST_ASSERT_MESSAGE(item1 != NULL, "Failed to receive item");

    //Check data of received item(s) and return them
    if (item2 == NULL) {
        TEST_ASSERT_MESSAGE(item_size1 == expected_size, "Item size is incorrect");
        for (int i = 0; i < item_size1; i++) {
            TEST_ASSERT_MESSAGE(item1[i] == expected_data[i], "Item data is invalid");
        }
        //Return item
        if (in_isr) {
            vRingbufferReturnItemFromISR(handle, (void *)item1, NULL);
        } else {
            vRingbufferReturnItem(handle, (void *)item1);
        }
    } else {
        //Item was split
        TEST_ASSERT_MESSAGE(item_size1 + item_size2 == expected_size, "Total item size is incorrect");
        for (int i = 0; i < item_size1; i++) {
            TEST_ASSERT_MESSAGE(item1[i] == expected_data[i], "Head item data is invalid");
        }
        for (int i = 0; i < item_size2; i++) {
            TEST_ASSERT_MESSAGE(item2[i] == expected_data[item_size1 + i], "Head item data is invalid");
        }
        //Return Items
        if (in_isr) {
            vRingbufferReturnItemFromISR(handle, (void *)item1, NULL);
            vRingbufferReturnItemFromISR(handle, (void *)item2, NULL);
        } else {
            vRingbufferReturnItem(handle, (void *)item1);
            vRingbufferReturnItem(handle, (void *)item2);
        }
    }
}