#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_1__* (* get_address ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  const* address; } ;

/* Variables and functions */
 scalar_t__ ESP_BLUEDROID_STATUS_ENABLED ; 
 TYPE_2__* controller_get_interface () ; 
 scalar_t__ esp_bluedroid_get_status () ; 
 TYPE_1__* stub1 () ; 

const uint8_t *esp_bt_dev_get_address(void)
{
    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
	return NULL;
    }
    return controller_get_interface()->get_address()->address;
}