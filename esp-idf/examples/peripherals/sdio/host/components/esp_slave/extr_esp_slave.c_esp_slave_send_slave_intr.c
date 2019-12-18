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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HOST_SLCHOST_CONF_W7_REG ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_slave_write_byte (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

esp_err_t esp_slave_send_slave_intr(esp_slave_context_t *context, uint8_t intr_mask)
{
    ESP_LOGV(TAG, "send_slave_intr: %02x", intr_mask);
    return esp_slave_write_byte(context, HOST_SLCHOST_CONF_W7_REG+0, intr_mask, NULL);
}