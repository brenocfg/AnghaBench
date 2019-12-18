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
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 TYPE_1__ data_buffer ; 
 int /*<<< orphan*/  esp_receive_apple_data_source (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  esp_timer_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  periodic_timer ; 

__attribute__((used)) static void periodic_timer_callback(void* arg)
{
    esp_timer_stop(periodic_timer);
    if (data_buffer.len > 0) {
        esp_receive_apple_data_source(data_buffer.buffer, data_buffer.len);
        memset(data_buffer.buffer, 0, data_buffer.len);
        data_buffer.len = 0;
    } 
}