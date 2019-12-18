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

/* Variables and functions */
 int /*<<< orphan*/  RINGBUF_TYPE_BYTEBUF ; 
 int /*<<< orphan*/  bt_i2s_task_handler ; 
 scalar_t__ configMAX_PRIORITIES ; 
 int /*<<< orphan*/  s_bt_i2s_task_handle ; 
 int /*<<< orphan*/ * s_ringbuf_i2s ; 
 int /*<<< orphan*/ * xRingbufferCreate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

void bt_i2s_task_start_up(void)
{
    s_ringbuf_i2s = xRingbufferCreate(8 * 1024, RINGBUF_TYPE_BYTEBUF);
    if(s_ringbuf_i2s == NULL){
        return;
    }

    xTaskCreate(bt_i2s_task_handler, "BtI2ST", 1024, NULL, configMAX_PRIORITIES - 3, &s_bt_i2s_task_handle);
    return;
}