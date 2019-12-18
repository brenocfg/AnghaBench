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
struct TYPE_2__ {int /*<<< orphan*/  mutex; scalar_t__ data; } ;
typedef  TYPE_1__ simple_arg_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_event_simple_handler(void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (!event_handler_arg) {
        return;
    }
    simple_arg_t* arg = (simple_arg_t*) event_handler_arg;
    xSemaphoreTake(arg->mutex, portMAX_DELAY);

    int* count = (int*) arg->data;

    if (event_data == NULL) {
        (*count)++;
    } else {
        (*count) += *((int*) event_data);
    }

    xSemaphoreGive(arg->mutex);
}