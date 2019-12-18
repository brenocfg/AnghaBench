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
typedef  scalar_t__ nmea_parser_handle_t ;
struct TYPE_3__ {struct TYPE_3__* buffer; int /*<<< orphan*/  uart_port; int /*<<< orphan*/  event_loop_hdl; int /*<<< orphan*/  tsk_hdl; } ;
typedef  TYPE_1__ esp_gps_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_event_loop_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_driver_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ ) ; 

esp_err_t nmea_parser_deinit(nmea_parser_handle_t nmea_hdl)
{
    esp_gps_t *esp_gps = (esp_gps_t *)nmea_hdl;
    vTaskDelete(esp_gps->tsk_hdl);
    esp_event_loop_delete(esp_gps->event_loop_hdl);
    esp_err_t err = uart_driver_delete(esp_gps->uart_port);
    free(esp_gps->buffer);
    free(esp_gps);
    return err;
}