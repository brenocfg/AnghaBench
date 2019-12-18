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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct bt_mesh_model {struct bt_mesh_light_lc_setup_srv* user_data; } ;
struct bt_mesh_light_lc_setup_srv {TYPE_2__* lc; } ;
struct TYPE_3__ {int /*<<< orphan*/  regulator_accuracy; int /*<<< orphan*/  regulator_kpd; int /*<<< orphan*/  regulator_kpu; int /*<<< orphan*/  regulator_kid; int /*<<< orphan*/  regulator_kiu; int /*<<< orphan*/  ambient_luxlevel_standby; int /*<<< orphan*/  ambient_luxlevel_prolong; int /*<<< orphan*/  ambient_luxlevel_on; int /*<<< orphan*/  lightness_standby; int /*<<< orphan*/  lightness_prolong; int /*<<< orphan*/  lightness_on; int /*<<< orphan*/  time_fade_standby_manual; int /*<<< orphan*/  time_fade_standby_auto; int /*<<< orphan*/  time_prolong; int /*<<< orphan*/  time_fade; int /*<<< orphan*/  time_run_on; int /*<<< orphan*/  time_fade_on; int /*<<< orphan*/  time_occupancy_delay; } ;
struct TYPE_4__ {TYPE_1__ prop_state; } ;

/* Variables and functions */
#define  BLE_MESH_LIGHT_CONTROL_AMBIENT_LUXLEVEL_ON 145 
#define  BLE_MESH_LIGHT_CONTROL_AMBIENT_LUXLEVEL_PROLONG 144 
#define  BLE_MESH_LIGHT_CONTROL_AMBIENT_LUXLEVEL_STANDBY 143 
#define  BLE_MESH_LIGHT_CONTROL_LIGHTNESS_ON 142 
#define  BLE_MESH_LIGHT_CONTROL_LIGHTNESS_PROLONG 141 
#define  BLE_MESH_LIGHT_CONTROL_LIGHTNESS_STANDBY 140 
#define  BLE_MESH_LIGHT_CONTROL_REGULATOR_ACCURACY 139 
#define  BLE_MESH_LIGHT_CONTROL_REGULATOR_KID 138 
#define  BLE_MESH_LIGHT_CONTROL_REGULATOR_KIU 137 
#define  BLE_MESH_LIGHT_CONTROL_REGULATOR_KPD 136 
#define  BLE_MESH_LIGHT_CONTROL_REGULATOR_KPU 135 
#define  BLE_MESH_LIGHT_CONTROL_TIME_FADE 134 
#define  BLE_MESH_LIGHT_CONTROL_TIME_FADE_ON 133 
#define  BLE_MESH_LIGHT_CONTROL_TIME_FADE_STANDBY_AUTO 132 
#define  BLE_MESH_LIGHT_CONTROL_TIME_FADE_STANDBY_MANUAL 131 
#define  BLE_MESH_LIGHT_CONTROL_TIME_OCCUPANCY_DELAY 130 
#define  BLE_MESH_LIGHT_CONTROL_TIME_PROLONG 129 
#define  BLE_MESH_LIGHT_CONTROL_TIME_RUN_ON 128 

__attribute__((used)) static u8_t *get_light_lc_prop_val(struct bt_mesh_model *model, u16_t prop_id)
{
    struct bt_mesh_light_lc_setup_srv *srv = model->user_data;
    u8_t *val = NULL;

    switch (prop_id) {
    case BLE_MESH_LIGHT_CONTROL_TIME_OCCUPANCY_DELAY:
        val = (u8_t *)&srv->lc->prop_state.time_occupancy_delay;
        break;
    case BLE_MESH_LIGHT_CONTROL_TIME_FADE_ON:
        val = (u8_t *)&srv->lc->prop_state.time_fade_on;
        break;
    case BLE_MESH_LIGHT_CONTROL_TIME_RUN_ON:
        val = (u8_t *)&srv->lc->prop_state.time_run_on;
        break;
    case BLE_MESH_LIGHT_CONTROL_TIME_FADE:
        val = (u8_t *)&srv->lc->prop_state.time_fade;
        break;
    case BLE_MESH_LIGHT_CONTROL_TIME_PROLONG:
        val = (u8_t *)&srv->lc->prop_state.time_prolong;
        break;
    case BLE_MESH_LIGHT_CONTROL_TIME_FADE_STANDBY_AUTO:
        val = (u8_t *)&srv->lc->prop_state.time_fade_standby_auto;
        break;
    case BLE_MESH_LIGHT_CONTROL_TIME_FADE_STANDBY_MANUAL:
        val = (u8_t *)&srv->lc->prop_state.time_fade_standby_manual;
        break;
    case BLE_MESH_LIGHT_CONTROL_LIGHTNESS_ON:
        val = (u8_t *)&srv->lc->prop_state.lightness_on;
        break;
    case BLE_MESH_LIGHT_CONTROL_LIGHTNESS_PROLONG:
        val = (u8_t *)&srv->lc->prop_state.lightness_prolong;
        break;
    case BLE_MESH_LIGHT_CONTROL_LIGHTNESS_STANDBY:
        val = (u8_t *)&srv->lc->prop_state.lightness_standby;
        break;
    case BLE_MESH_LIGHT_CONTROL_AMBIENT_LUXLEVEL_ON:
        val = (u8_t *)&srv->lc->prop_state.ambient_luxlevel_on;
        break;
    case BLE_MESH_LIGHT_CONTROL_AMBIENT_LUXLEVEL_PROLONG:
        val = (u8_t *)&srv->lc->prop_state.ambient_luxlevel_prolong;
        break;
    case BLE_MESH_LIGHT_CONTROL_AMBIENT_LUXLEVEL_STANDBY:
        val = (u8_t *)&srv->lc->prop_state.ambient_luxlevel_standby;
        break;
    case BLE_MESH_LIGHT_CONTROL_REGULATOR_KIU:
        val = (u8_t *)&srv->lc->prop_state.regulator_kiu;
        break;
    case BLE_MESH_LIGHT_CONTROL_REGULATOR_KID:
        val = (u8_t *)&srv->lc->prop_state.regulator_kid;
        break;
    case BLE_MESH_LIGHT_CONTROL_REGULATOR_KPU:
        val = (u8_t *)&srv->lc->prop_state.regulator_kpu;
        break;
    case BLE_MESH_LIGHT_CONTROL_REGULATOR_KPD:
        val = (u8_t *)&srv->lc->prop_state.regulator_kpd;
        break;
    case BLE_MESH_LIGHT_CONTROL_REGULATOR_ACCURACY:
        val = (u8_t *)&srv->lc->prop_state.regulator_accuracy;
        break;
    }

    return val;
}