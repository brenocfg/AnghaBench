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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  portTickType ;

/* Variables and functions */
 int /*<<< orphan*/  i2s_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*,scalar_t__) ; 
 scalar_t__ portMAX_DELAY ; 
 int /*<<< orphan*/  s_ringbuf_i2s ; 
 int /*<<< orphan*/  vRingbufferReturnItem (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ xRingbufferReceive (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt_i2s_task_handler(void *arg)
{
    uint8_t *data = NULL;
    size_t item_size = 0;
    size_t bytes_written = 0;

    for (;;) {
        data = (uint8_t *)xRingbufferReceive(s_ringbuf_i2s, &item_size, (portTickType)portMAX_DELAY);
        if (item_size != 0){
            i2s_write(0, data, item_size, &bytes_written, portMAX_DELAY);
            vRingbufferReturnItem(s_ringbuf_i2s,(void *)data);
        }
    }
}