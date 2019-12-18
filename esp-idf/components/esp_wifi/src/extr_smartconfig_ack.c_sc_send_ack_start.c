#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  smartconfig_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  token; } ;
struct TYPE_7__ {TYPE_1__ ctx; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ sc_ack_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SC_ACK_TASK_PRIORITY ; 
 int /*<<< orphan*/  SC_ACK_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pdPASS ; 
 int s_sc_ack_send ; 
 int /*<<< orphan*/  sc_ack_send_task ; 
 scalar_t__ xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

esp_err_t sc_send_ack_start(smartconfig_type_t type, uint8_t token, uint8_t *cellphone_ip)
{
    sc_ack_t *ack = NULL;

    if (cellphone_ip == NULL) {
        ESP_LOGE(TAG, "Cellphone IP address is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    ack = malloc(sizeof(sc_ack_t));
    if (ack == NULL) {
        ESP_LOGE(TAG, "ACK parameter malloc fail");
        return ESP_ERR_NO_MEM;
    }
    ack->type = type;
    ack->ctx.token = token;
    memcpy(ack->ctx.ip, cellphone_ip, 4);

    s_sc_ack_send = true;

    if (xTaskCreate(sc_ack_send_task, "sc_ack_send_task", SC_ACK_TASK_STACK_SIZE, ack, SC_ACK_TASK_PRIORITY, NULL) != pdPASS) {
        ESP_LOGE(TAG, "Create sending smartconfig ACK task fail");
        free(ack);
        return ESP_ERR_NO_MEM;
    }

    return ESP_OK;
}