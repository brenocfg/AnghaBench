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
struct TYPE_4__ {int /*<<< orphan*/ * global_transport_ctx; int /*<<< orphan*/  (* global_transport_ctx_free_fn ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * global_user_ctx; int /*<<< orphan*/  (* global_user_ctx_free_fn ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  ctrl_port; } ;
struct TYPE_3__ {scalar_t__ status; } ;
struct httpd_data {TYPE_2__ config; TYPE_1__ hd_td; int /*<<< orphan*/  msg_fd; } ;
struct httpd_ctrl_data {int /*<<< orphan*/  hc_msg; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HTTPD_CTRL_SHUTDOWN ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ THREAD_STOPPED ; 
 int /*<<< orphan*/  cs_send_to_ctrl_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct httpd_ctrl_data*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpd_delete (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_os_thread_sleep (int) ; 
 int /*<<< orphan*/  memset (struct httpd_ctrl_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

esp_err_t httpd_stop(httpd_handle_t handle)
{
    struct httpd_data *hd = (struct httpd_data *) handle;
    if (hd == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    struct httpd_ctrl_data msg;
    memset(&msg, 0, sizeof(msg));
    msg.hc_msg = HTTPD_CTRL_SHUTDOWN;
    cs_send_to_ctrl_sock(hd->msg_fd, hd->config.ctrl_port, &msg, sizeof(msg));

    ESP_LOGD(TAG, LOG_FMT("sent control msg to stop server"));
    while (hd->hd_td.status != THREAD_STOPPED) {
        httpd_os_thread_sleep(100);
    }

    /* Release global user context, if not NULL */
    if (hd->config.global_user_ctx) {
        if (hd->config.global_user_ctx_free_fn) {
            hd->config.global_user_ctx_free_fn(hd->config.global_user_ctx);
        } else {
            free(hd->config.global_user_ctx);
        }
        hd->config.global_user_ctx = NULL;
    }

    /* Release global transport context, if not NULL */
    if (hd->config.global_transport_ctx) {
        if (hd->config.global_transport_ctx_free_fn) {
            hd->config.global_transport_ctx_free_fn(hd->config.global_transport_ctx);
        } else {
            free(hd->config.global_transport_ctx);
        }
        hd->config.global_transport_ctx = NULL;
    }

    ESP_LOGD(TAG, LOG_FMT("server stopped"));
    httpd_delete(hd);
    return ESP_OK;
}