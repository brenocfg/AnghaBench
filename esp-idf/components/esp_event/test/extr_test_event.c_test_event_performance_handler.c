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
struct TYPE_2__ {scalar_t__ performed; scalar_t__ expected; int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ performance_data_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_event_performance_handler(void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    performance_data_t* data = (performance_data_t*) event_handler_arg;

    data->performed++;

    if (data->performed >= data->expected) {
        xSemaphoreGive(data->done);
    }
}