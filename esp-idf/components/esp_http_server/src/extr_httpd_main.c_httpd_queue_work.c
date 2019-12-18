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
struct TYPE_2__ {int /*<<< orphan*/  ctrl_port; } ;
struct httpd_data {TYPE_1__ config; int /*<<< orphan*/  msg_fd; } ;
struct httpd_ctrl_data {void* hc_work_arg; int /*<<< orphan*/ * hc_work; int /*<<< orphan*/  hc_msg; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/ * httpd_work_fn_t ;
typedef  int /*<<< orphan*/ * httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HTTPD_CTRL_WORK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int cs_send_to_ctrl_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct httpd_ctrl_data*,int) ; 

esp_err_t httpd_queue_work(httpd_handle_t handle, httpd_work_fn_t work, void *arg)
{
    if (handle == NULL || work == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    struct httpd_data *hd = (struct httpd_data *) handle;
    struct httpd_ctrl_data msg = {
        .hc_msg = HTTPD_CTRL_WORK,
        .hc_work = work,
        .hc_work_arg = arg,
    };

    int ret = cs_send_to_ctrl_sock(hd->msg_fd, hd->config.ctrl_port, &msg, sizeof(msg));
    if (ret < 0) {
        ESP_LOGW(TAG, LOG_FMT("failed to queue work"));
        return ESP_FAIL;
    }

    return ESP_OK;
}