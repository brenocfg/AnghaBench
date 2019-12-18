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
typedef  size_t u8_t ;
typedef  scalar_t__ u16_t ;
struct sensor_setting {scalar_t__ property_id; } ;
struct bt_mesh_sensor_state {scalar_t__ sensor_property_id; size_t setting_count; struct sensor_setting* settings; } ;
struct bt_mesh_sensor_setup_srv {size_t state_count; struct bt_mesh_sensor_state* states; } ;
struct bt_mesh_model {struct bt_mesh_sensor_setup_srv* user_data; } ;

/* Variables and functions */
 scalar_t__ INVALID_SENSOR_PROPERTY_ID ; 
 scalar_t__ INVALID_SENSOR_SETTING_PROPERTY_ID ; 

__attribute__((used)) static struct sensor_setting *find_sensor_setting(struct bt_mesh_model *model,
        u16_t prop_id, u16_t set_prop_id)
{
    struct bt_mesh_sensor_setup_srv *srv = model->user_data;
    struct bt_mesh_sensor_state *state = NULL;
    struct sensor_setting *item = NULL;
    u8_t i, j;

    for (i = 0U; i < srv->state_count; i++) {
        state = &srv->states[i];
        if (state->sensor_property_id != INVALID_SENSOR_PROPERTY_ID &&
                state->sensor_property_id == prop_id) {
            for (j = 0U; j < state->setting_count; j++) {
                item = &state->settings[j];
                if (item->property_id != INVALID_SENSOR_SETTING_PROPERTY_ID &&
                        item->property_id == set_prop_id) {
                    return item;
                }
            }
        }
    }

    return NULL;
}