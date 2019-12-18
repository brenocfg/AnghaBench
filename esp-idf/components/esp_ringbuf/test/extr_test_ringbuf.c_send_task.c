#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ task_args_t ;
typedef  int /*<<< orphan*/  RingbufHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_to_buffer (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 size_t xRingbufferGetMaxItemSize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_task(void *args)
{
    RingbufHandle_t buffer = ((task_args_t *)args)->buffer;
    size_t max_item_len = xRingbufferGetMaxItemSize(buffer);

    //Test sending short length items
    send_to_buffer(buffer, 1);
    //Test sending mid length items
    send_to_buffer(buffer, max_item_len/2);
    //Test sending long length items
    send_to_buffer(buffer, max_item_len);
    vTaskDelete(NULL);
}