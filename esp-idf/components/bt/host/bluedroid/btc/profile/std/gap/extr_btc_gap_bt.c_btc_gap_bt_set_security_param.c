#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int param_type; int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ set_security_param; } ;
typedef  TYPE_2__ btc_gap_bt_args_t ;

/* Variables and functions */
#define  ESP_BT_SP_IOCAP_MODE 128 
 int /*<<< orphan*/  ESP_BT_STATUS_FAIL ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_dm_co_bt_set_io_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t btc_gap_bt_set_security_param(btc_gap_bt_args_t *arg)
{
    esp_err_t ret;
    switch(arg->set_security_param.param_type) {
    case ESP_BT_SP_IOCAP_MODE:{
        uint8_t iocap = 0;
        uint8_t *p = arg->set_security_param.value;
        STREAM_TO_UINT8(iocap, p);
        ret = bta_dm_co_bt_set_io_cap(iocap);
        break;
    }
    default:
        ret = ESP_BT_STATUS_FAIL;
        break;
    }
    return ret;
}