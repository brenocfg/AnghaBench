#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int type; int /*<<< orphan*/  value; } ;
typedef  TYPE_8__ tBTA_HF_CLIENT_IND ;
struct TYPE_19__ {int /*<<< orphan*/  value; } ;
struct TYPE_18__ {int /*<<< orphan*/  status; } ;
struct TYPE_17__ {int /*<<< orphan*/  value; } ;
struct TYPE_16__ {int /*<<< orphan*/  status; } ;
struct TYPE_15__ {int /*<<< orphan*/  status; } ;
struct TYPE_14__ {int /*<<< orphan*/  status; } ;
struct TYPE_13__ {int /*<<< orphan*/  status; } ;
struct TYPE_21__ {TYPE_7__ battery_level; TYPE_6__ roaming; TYPE_5__ signal_strength; TYPE_4__ service_availability; TYPE_3__ call_held; TYPE_2__ call_setup; TYPE_1__ call; } ;
typedef  TYPE_9__ esp_hf_client_cb_param_t ;

/* Variables and functions */
#define  BTA_HF_CLIENT_IND_BATTCH 134 
#define  BTA_HF_CLIENT_IND_CALL 133 
#define  BTA_HF_CLIENT_IND_CALLHELD 132 
#define  BTA_HF_CLIENT_IND_CALLSETUP 131 
#define  BTA_HF_CLIENT_IND_ROAM 130 
#define  BTA_HF_CLIENT_IND_SERVICE 129 
#define  BTA_HF_CLIENT_IND_SIGNAL 128 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_BATTERY_LEVEL_EVT ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_CALL_EVT ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_CALL_HELD_EVT ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_CALL_SETUP_EVT ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_ROAMING_STATUS_EVT ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_SERVICE_AVAILABILITY_EVT ; 
 int /*<<< orphan*/  ESP_HF_CLIENT_CIND_SIGNAL_STRENGTH_EVT ; 
 int /*<<< orphan*/  btc_hf_client_cb_to_app (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void process_ind_evt(tBTA_HF_CLIENT_IND *ind)
{
    esp_hf_client_cb_param_t param;
    memset(&param, 0, sizeof(esp_hf_client_cb_param_t));

    switch (ind->type)
    {
        case BTA_HF_CLIENT_IND_CALL:
            param.call.status = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_CALL_EVT, &param);
            break;

        case BTA_HF_CLIENT_IND_CALLSETUP:
            param.call_setup.status = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_CALL_SETUP_EVT, &param);
            break;
        case BTA_HF_CLIENT_IND_CALLHELD:
            param.call_held.status = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_CALL_HELD_EVT, &param);
            break;

        case BTA_HF_CLIENT_IND_SERVICE:
            param.service_availability.status = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_SERVICE_AVAILABILITY_EVT, &param);
            break;

        case BTA_HF_CLIENT_IND_SIGNAL:
            param.signal_strength.value = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_SIGNAL_STRENGTH_EVT, &param);
            break;

        case BTA_HF_CLIENT_IND_ROAM:
            param.roaming.status = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_ROAMING_STATUS_EVT, &param);
            break;

        case BTA_HF_CLIENT_IND_BATTCH:
            param.battery_level.value = ind->value;
            btc_hf_client_cb_to_app(ESP_HF_CLIENT_CIND_BATTERY_LEVEL_EVT, &param);
            break;

        default:
            break;
    }
}