#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  event_info; int /*<<< orphan*/  event_id; } ;
typedef  TYPE_1__ system_event_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_event_base_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  esp_event_legacy_event_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_event_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_event_send_legacy (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 

esp_err_t esp_event_send_internal(esp_event_base_t event_base,
                            int32_t event_id,
                            void* event_data,
                            size_t event_data_size,
                            TickType_t ticks_to_wait)
{
    system_event_t event;

    // send the event to the new style event loop
    esp_err_t err = esp_event_post(event_base, event_id, event_data, event_data_size, ticks_to_wait);
    if (err != ESP_OK) {
        return err;
    }

    event.event_id = esp_event_legacy_event_id(event_base, event_id);

    if (event_data) {
        memcpy(&event.event_info, event_data, event_data_size);
    }

    return esp_event_send_legacy(&event);
}