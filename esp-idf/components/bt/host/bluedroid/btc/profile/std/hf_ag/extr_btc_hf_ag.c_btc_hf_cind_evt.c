#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ tBTA_AG_IND ;
struct TYPE_7__ {int /*<<< orphan*/  call_held_status; int /*<<< orphan*/  battery_level; int /*<<< orphan*/  roam; int /*<<< orphan*/  signal_strength; int /*<<< orphan*/  svc; int /*<<< orphan*/  call_setup_status; int /*<<< orphan*/  call_status; } ;
struct TYPE_9__ {TYPE_1__ cind; } ;
typedef  TYPE_3__ esp_hf_cb_param_t ;

/* Variables and functions */
#define  BTA_AG_IND_BATTCHG 134 
#define  BTA_AG_IND_CALL 133 
#define  BTA_AG_IND_CALLHELD 132 
#define  BTA_AG_IND_CALLSETUP 131 
#define  BTA_AG_IND_ROAM 130 
#define  BTA_AG_IND_SERVICE 129 
#define  BTA_AG_IND_SIGNAL 128 
 int /*<<< orphan*/  ESP_HF_CIND_RESPONSE_EVT ; 
 int /*<<< orphan*/  btc_hf_cb_to_app (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btc_hf_cind_evt(tBTA_AG_IND *ind)
{
    esp_hf_cb_param_t param;
    memset(&param, 0, sizeof(esp_hf_cb_param_t));

    switch (ind->type) {
        case BTA_AG_IND_CALL:
            param.cind.call_status = ind->value;
            break;
        case BTA_AG_IND_CALLSETUP:
            param.cind.call_setup_status = ind->value;
            break;
        case BTA_AG_IND_SERVICE:
            param.cind.svc = ind->value;
            break;
        case BTA_AG_IND_SIGNAL:
            param.cind.signal_strength = ind->value;
            break;
        case BTA_AG_IND_ROAM:
            param.cind.roam = ind->value;
            break;
        case BTA_AG_IND_BATTCHG:
            param.cind.battery_level = ind->value;
            break;
        case BTA_AG_IND_CALLHELD:
            param.cind.call_held_status = ind->value;
            break;
    }
    btc_hf_cb_to_app(ESP_HF_CIND_RESPONSE_EVT, &param);
}