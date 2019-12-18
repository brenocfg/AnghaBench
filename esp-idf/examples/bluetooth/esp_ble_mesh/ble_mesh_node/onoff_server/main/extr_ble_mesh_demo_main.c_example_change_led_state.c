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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
struct _led_state {int /*<<< orphan*/  pin; } ;
struct TYPE_8__ {scalar_t__ recv_dst; } ;
typedef  TYPE_2__ esp_ble_mesh_msg_ctx_t ;
struct TYPE_9__ {TYPE_1__* element; } ;
typedef  TYPE_3__ esp_ble_mesh_model_t ;
struct TYPE_7__ {scalar_t__ element_addr; } ;

/* Variables and functions */
 scalar_t__ ESP_BLE_MESH_ADDR_IS_GROUP (scalar_t__) ; 
 scalar_t__ ESP_BLE_MESH_ADDR_IS_UNICAST (scalar_t__) ; 
 int /*<<< orphan*/  board_led_operation (int /*<<< orphan*/ ,size_t) ; 
 size_t esp_ble_mesh_get_element_count () ; 
 scalar_t__ esp_ble_mesh_get_primary_element_address () ; 
 scalar_t__ esp_ble_mesh_is_model_subscribed_to_group (TYPE_3__*,scalar_t__) ; 
 struct _led_state* led_state ; 

__attribute__((used)) static void example_change_led_state(esp_ble_mesh_model_t *model,
                                     esp_ble_mesh_msg_ctx_t *ctx, uint8_t onoff)
{
    uint16_t primary_addr = esp_ble_mesh_get_primary_element_address();
    uint8_t elem_count = esp_ble_mesh_get_element_count();
    struct _led_state *led = NULL;
    uint8_t i;

    if (ESP_BLE_MESH_ADDR_IS_UNICAST(ctx->recv_dst)) {
        for (i = 0; i < elem_count; i++) {
            if (ctx->recv_dst == (primary_addr + i)) {
                led = &led_state[i];
                board_led_operation(led->pin, onoff);
            }
        }
    } else if (ESP_BLE_MESH_ADDR_IS_GROUP(ctx->recv_dst)) {
        if (esp_ble_mesh_is_model_subscribed_to_group(model, ctx->recv_dst)) {
            led = &led_state[model->element->element_addr - primary_addr];
            board_led_operation(led->pin, onoff);
        }
    } else if (ctx->recv_dst == 0xFFFF) {
        led = &led_state[model->element->element_addr - primary_addr];
        board_led_operation(led->pin, onoff);
    }
}