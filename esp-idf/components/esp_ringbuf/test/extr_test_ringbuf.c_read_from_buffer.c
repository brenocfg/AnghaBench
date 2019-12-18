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
typedef  scalar_t__ RingbufferType_t ;
typedef  int /*<<< orphan*/  RingbufHandle_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 size_t CONT_DATA_LEN ; 
 scalar_t__ RINGBUF_TYPE_ALLOWSPLIT ; 
 scalar_t__ RINGBUF_TYPE_BYTEBUF ; 
 scalar_t__ RINGBUF_TYPE_NOSPLIT ; 
 int SMP_TEST_ITERATIONS ; 
 int /*<<< orphan*/  TEST_ASSERT_MESSAGE (int,char*) ; 
 int /*<<< orphan*/  TIMEOUT_TICKS ; 
 char* continuous_data ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  rx_done ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xRingbufferReceive (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ xRingbufferReceiveSplit (int /*<<< orphan*/ ,void**,void**,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ xRingbufferReceiveUpTo (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_from_buffer(RingbufHandle_t buffer, RingbufferType_t buf_type, size_t max_rec_size)
{
    for (int iter = 0; iter < SMP_TEST_ITERATIONS; iter++) {
        size_t bytes_rec = 0;      //Number of data bytes received in this iteration
        while (bytes_rec < CONT_DATA_LEN) {
            size_t item_size, item_size2;    //Possible for allow split buffers to receive two items
            char *item_data, *item_data2;

            //Select appropriate receive function for type of ring buffer
            if (buf_type ==  RINGBUF_TYPE_NOSPLIT) {
                item_data = (char *)xRingbufferReceive(buffer, &item_size, TIMEOUT_TICKS);
            } else if (buf_type == RINGBUF_TYPE_ALLOWSPLIT) {
                BaseType_t ret = xRingbufferReceiveSplit(buffer, (void **)&item_data, (void **)&item_data2, &item_size, &item_size2, TIMEOUT_TICKS);
                TEST_ASSERT_MESSAGE(ret == pdTRUE, "Failed to receive any item");
            } else {
                item_data = (char *)xRingbufferReceiveUpTo(buffer, &item_size, TIMEOUT_TICKS, max_rec_size);
            }

            //Check received item and return it
            TEST_ASSERT_MESSAGE(item_data != NULL, "Failed to receive an item");
            if (buf_type == RINGBUF_TYPE_BYTEBUF) {
                TEST_ASSERT_MESSAGE(item_size <= max_rec_size, "Received data exceeds max size");
            }
            for (int i = 0; i < item_size; i++) {
                //Check item_data is valid
                TEST_ASSERT_MESSAGE(item_data[i] == continuous_data[bytes_rec + i], "Received data is corrupted");
            }
            bytes_rec += item_size;
            vRingbufferReturnItem(buffer, item_data);
            if (buf_type == RINGBUF_TYPE_ALLOWSPLIT && item_data2 != NULL) {
                //Check item_data2 is valid
                for (int i = 0; i < item_size2; i++) {
                    TEST_ASSERT_MESSAGE(item_data2[i] == continuous_data[bytes_rec + i], "Received split data is corrupted");
                }
                bytes_rec += item_size2;
                vRingbufferReturnItem(buffer, item_data2);
            }
        }
        TEST_ASSERT_MESSAGE(bytes_rec == CONT_DATA_LEN, "Total length of received data is incorrect");
        xSemaphoreGive(rx_done);
        xSemaphoreTake(tx_done, portMAX_DELAY);
    }
}