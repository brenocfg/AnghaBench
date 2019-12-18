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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_ble_gatts_register_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatts_event_handler ; 

esp_err_t hidd_register_cb(void)
{
	esp_err_t status;
	status = esp_ble_gatts_register_callback(gatts_event_handler);
	return status;
}