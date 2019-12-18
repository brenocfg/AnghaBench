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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ token_id; scalar_t__ token_value; scalar_t__ cmd; scalar_t__ on; } ;
typedef  TYPE_1__ mesh_light_ctl_t ;
typedef  int /*<<< orphan*/  mesh_addr_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MESH_CONTROL_CMD ; 
 scalar_t__ MESH_TOKEN_ID ; 
 scalar_t__ MESH_TOKEN_VALUE ; 
 int /*<<< orphan*/  esp_mesh_get_layer () ; 
 int /*<<< orphan*/  mesh_connected_indicator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_light_set (int /*<<< orphan*/ ) ; 

esp_err_t mesh_light_process(mesh_addr_t *from, uint8_t *buf, uint16_t len)
{
    mesh_light_ctl_t *in = (mesh_light_ctl_t *) buf;
    if (!from || !buf || len < sizeof(mesh_light_ctl_t)) {
        return ESP_FAIL;
    }
    if (in->token_id != MESH_TOKEN_ID || in->token_value != MESH_TOKEN_VALUE) {
        return ESP_FAIL;
    }
    if (in->cmd == MESH_CONTROL_CMD) {
        if (in->on) {
            mesh_connected_indicator(esp_mesh_get_layer());
        } else {
            mesh_light_set(0);
        }
    }
    return ESP_OK;
}