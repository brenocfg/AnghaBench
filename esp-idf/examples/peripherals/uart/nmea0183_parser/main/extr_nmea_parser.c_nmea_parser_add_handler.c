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
typedef  scalar_t__ nmea_parser_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  event_loop_hdl; } ;
typedef  TYPE_1__ esp_gps_t ;
typedef  int /*<<< orphan*/  esp_event_handler_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EVENT_ANY_ID ; 
 int /*<<< orphan*/  ESP_NMEA_EVENT ; 
 int /*<<< orphan*/  esp_event_handler_register_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

esp_err_t nmea_parser_add_handler(nmea_parser_handle_t nmea_hdl, esp_event_handler_t event_handler, void *handler_args)
{
    esp_gps_t *esp_gps = (esp_gps_t *)nmea_hdl;
    return esp_event_handler_register_with(esp_gps->event_loop_hdl, ESP_NMEA_EVENT, ESP_EVENT_ANY_ID,
                                           event_handler, handler_args);
}