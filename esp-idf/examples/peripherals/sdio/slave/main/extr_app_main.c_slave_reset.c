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
typedef  int /*<<< orphan*/  sdio_slave_buf_handle_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ sdio_slave_recv_load_buf (int /*<<< orphan*/ ) ; 
 scalar_t__ sdio_slave_reset () ; 
 scalar_t__ sdio_slave_send_get_finished (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sdio_slave_start () ; 
 int /*<<< orphan*/  sdio_slave_stop () ; 

__attribute__((used)) static esp_err_t slave_reset(void)
{
    esp_err_t ret;
    sdio_slave_stop();
    ret = sdio_slave_reset();
    if (ret != ESP_OK) return ret;
    ret = sdio_slave_start();
    if (ret != ESP_OK) return ret;

    //Since the buffer will not be sent any more, we return them back to receving driver
    while(1) {
        sdio_slave_buf_handle_t handle;
        ret = sdio_slave_send_get_finished(&handle, 0);
        if (ret != ESP_OK) break;
        ret = sdio_slave_recv_load_buf(handle);
        ESP_ERROR_CHECK(ret);
    }
    return ESP_OK;
}