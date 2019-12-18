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

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_MESSAGE (int,char*) ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vRingbufferReturnItemFromISR (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ xRingbufferReceive (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ xRingbufferReceiveFromISR (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void receive_check_and_return_item_no_split(RingbufHandle_t handle, const uint8_t *expected_data, size_t expected_size, TickType_t ticks_to_wait, bool in_isr)
{
    //Receive item from no-split buffer
    size_t item_size;
    uint8_t *item;
    if (in_isr) {
        item = (uint8_t *)xRingbufferReceiveFromISR(handle, &item_size);
    } else {
        item = (uint8_t *)xRingbufferReceive(handle, &item_size, ticks_to_wait);
    }
    TEST_ASSERT_MESSAGE(item != NULL, "Failed to receive item");
    TEST_ASSERT_MESSAGE(item_size == expected_size, "Item size is incorrect");
    //Check data of received item
    for (int i = 0; i < item_size; i++) {
        TEST_ASSERT_MESSAGE(item[i] == expected_data[i], "Item data is invalid");
    }
    //Return item
    if (in_isr) {
        vRingbufferReturnItemFromISR(handle, (void *)item, NULL);
    } else {
        vRingbufferReturnItem(handle, (void *)item);
    }

}