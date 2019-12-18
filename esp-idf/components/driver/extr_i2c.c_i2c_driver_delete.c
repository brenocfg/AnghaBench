#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t i2c_port_t ;
struct TYPE_7__ {struct TYPE_7__* evt_queue_storage; int /*<<< orphan*/ * pm_lock; scalar_t__ tx_buf_length; int /*<<< orphan*/ * tx_ring_buf; scalar_t__ rx_buf_length; int /*<<< orphan*/ * rx_ring_buf; scalar_t__ slv_tx_mux; scalar_t__ slv_rx_mux; int /*<<< orphan*/ * cmd_evt_queue; scalar_t__ cmd_mux; int /*<<< orphan*/ * intr_handle; } ;
typedef  TYPE_2__ i2c_obj_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {scalar_t__ val; } ;
struct TYPE_8__ {TYPE_1__ int_ena; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__** I2C ; 
 int /*<<< orphan*/  I2C_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_DRIVER_ERR_STR ; 
 int /*<<< orphan*/  I2C_NUM_ERROR_STR ; 
 size_t I2C_NUM_MAX ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_pm_lock_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_hw_disable (size_t) ; 
 TYPE_2__** p_i2c_obj ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vRingbufferDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (scalar_t__) ; 
 int /*<<< orphan*/  xSemaphoreTake (scalar_t__,int /*<<< orphan*/ ) ; 

esp_err_t i2c_driver_delete(i2c_port_t i2c_num)
{
    I2C_CHECK(i2c_num < I2C_NUM_MAX, I2C_NUM_ERROR_STR, ESP_ERR_INVALID_ARG);
    I2C_CHECK(p_i2c_obj[i2c_num] != NULL, I2C_DRIVER_ERR_STR, ESP_FAIL);

    i2c_obj_t* p_i2c = p_i2c_obj[i2c_num];

    I2C[i2c_num]->int_ena.val = 0;
    esp_intr_free(p_i2c->intr_handle);
    p_i2c->intr_handle = NULL;

    if (p_i2c->cmd_mux) {
        xSemaphoreTake(p_i2c->cmd_mux, portMAX_DELAY);
        vSemaphoreDelete(p_i2c->cmd_mux);
    }
    if (p_i2c_obj[i2c_num]->cmd_evt_queue) {
        vQueueDelete(p_i2c_obj[i2c_num]->cmd_evt_queue);
        p_i2c_obj[i2c_num]->cmd_evt_queue = NULL;
    }
    if (p_i2c->slv_rx_mux) {
        vSemaphoreDelete(p_i2c->slv_rx_mux);
    }
    if (p_i2c->slv_tx_mux) {
        vSemaphoreDelete(p_i2c->slv_tx_mux);
    }

    if (p_i2c->rx_ring_buf) {
        vRingbufferDelete(p_i2c->rx_ring_buf);
        p_i2c->rx_ring_buf = NULL;
        p_i2c->rx_buf_length = 0;
    }
    if (p_i2c->tx_ring_buf) {
        vRingbufferDelete(p_i2c->tx_ring_buf);
        p_i2c->tx_ring_buf = NULL;
        p_i2c->tx_buf_length = 0;
    }
#ifdef CONFIG_PM_ENABLE
        if (p_i2c->pm_lock) {
            esp_pm_lock_delete(p_i2c->pm_lock);
            p_i2c->pm_lock = NULL;
        }
#endif
#if CONFIG_SPIRAM_USE_MALLOC
    if (p_i2c_obj[i2c_num]->evt_queue_storage) {
        free(p_i2c_obj[i2c_num]->evt_queue_storage);
        p_i2c_obj[i2c_num]->evt_queue_storage = NULL;
    }
#endif

    free(p_i2c_obj[i2c_num]);
    p_i2c_obj[i2c_num] = NULL;

    i2c_hw_disable(i2c_num);
    return ESP_OK;
}