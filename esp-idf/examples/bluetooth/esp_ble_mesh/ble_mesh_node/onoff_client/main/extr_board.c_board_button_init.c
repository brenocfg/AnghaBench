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
typedef  scalar_t__ button_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_ACTIVE_LEVEL ; 
 int /*<<< orphan*/  BUTTON_CB_RELEASE ; 
 int /*<<< orphan*/  BUTTON_IO_NUM ; 
 int /*<<< orphan*/  button_tap_cb ; 
 scalar_t__ iot_button_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iot_button_set_evt_cb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void board_button_init(void)
{
    button_handle_t btn_handle = iot_button_create(BUTTON_IO_NUM, BUTTON_ACTIVE_LEVEL);
    if (btn_handle) {
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, "RELEASE");
    }
}