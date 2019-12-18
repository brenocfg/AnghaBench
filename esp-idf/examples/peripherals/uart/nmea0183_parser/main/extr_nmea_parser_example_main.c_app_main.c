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
typedef  int /*<<< orphan*/  nmea_parser_handle_t ;
typedef  int /*<<< orphan*/  nmea_parser_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  NMEA_PARSER_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  gps_event_handler ; 
 int /*<<< orphan*/  nmea_parser_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmea_parser_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmea_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nmea_parser_remove_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void app_main(void)
{
    /* NMEA parser configuration */
    nmea_parser_config_t config = NMEA_PARSER_CONFIG_DEFAULT();
    /* init NMEA parser library */
    nmea_parser_handle_t nmea_hdl = nmea_parser_init(&config);
    /* register event handler for NMEA parser library */
    nmea_parser_add_handler(nmea_hdl, gps_event_handler, NULL);

    vTaskDelay(10000 / portTICK_PERIOD_MS);

    /* unregister event handler */
    nmea_parser_remove_handler(nmea_hdl, gps_event_handler);
    /* deinit NMEA parser library */
    nmea_parser_deinit(nmea_hdl);
}