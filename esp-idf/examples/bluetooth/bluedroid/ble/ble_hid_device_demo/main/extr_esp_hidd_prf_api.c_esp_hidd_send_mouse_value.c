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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  gatt_if; } ;

/* Variables and functions */
 int HID_MOUSE_IN_RPT_LEN ; 
 int /*<<< orphan*/  HID_REPORT_TYPE_INPUT ; 
 int /*<<< orphan*/  HID_RPT_ID_MOUSE_IN ; 
 int /*<<< orphan*/  hid_dev_send_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 TYPE_1__ hidd_le_env ; 

void esp_hidd_send_mouse_value(uint16_t conn_id, uint8_t mouse_button, int8_t mickeys_x, int8_t mickeys_y)
{
    uint8_t buffer[HID_MOUSE_IN_RPT_LEN];
    
    buffer[0] = mouse_button;   // Buttons
    buffer[1] = mickeys_x;           // X
    buffer[2] = mickeys_y;           // Y
    buffer[3] = 0;           // Wheel
    buffer[4] = 0;           // AC Pan

    hid_dev_send_report(hidd_le_env.gatt_if, conn_id,
                        HID_RPT_ID_MOUSE_IN, HID_REPORT_TYPE_INPUT, HID_MOUSE_IN_RPT_LEN, buffer);
    return;
}