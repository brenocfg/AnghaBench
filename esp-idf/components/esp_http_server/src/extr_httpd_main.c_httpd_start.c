#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  core_id; int /*<<< orphan*/  task_priority; int /*<<< orphan*/  stack_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct httpd_data {TYPE_2__ config; TYPE_1__ hd_td; } ;
typedef  int /*<<< orphan*/ **** httpd_handle_t ;
struct TYPE_8__ {scalar_t__ max_open_sockets; } ;
typedef  TYPE_3__ httpd_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ CONFIG_LWIP_MAX_SOCKETS ; 
 scalar_t__ ESP_ERR_HTTPD_ALLOC_MEM ; 
 scalar_t__ ESP_ERR_HTTPD_TASK ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 struct httpd_data* httpd_create (TYPE_3__ const*) ; 
 int /*<<< orphan*/  httpd_delete (struct httpd_data*) ; 
 scalar_t__ httpd_os_thread_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct httpd_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ httpd_server_init (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_sess_init (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_thread ; 

esp_err_t httpd_start(httpd_handle_t *handle, const httpd_config_t *config)
{
    if (handle == NULL || config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Sanity check about whether LWIP is configured for providing the
     * maximum number of open sockets sufficient for the server. Though,
     * this check doesn't guarantee that many sockets will actually be
     * available at runtime as other processes may use up some sockets.
     * Note that server also uses 3 sockets for its internal use :
     *     1) listening for new TCP connections
     *     2) for sending control messages over UDP
     *     3) for receiving control messages over UDP
     * So the total number of required sockets is max_open_sockets + 3
     */
    if (CONFIG_LWIP_MAX_SOCKETS < config->max_open_sockets + 3) {
        ESP_LOGE(TAG, "Configuration option max_open_sockets is too large (max allowed %d)\n\t"
                      "Either decrease this or configure LWIP_MAX_SOCKETS to a larger value",
                      CONFIG_LWIP_MAX_SOCKETS - 3);
        return ESP_ERR_INVALID_ARG;
    }

    struct httpd_data *hd = httpd_create(config);
    if (hd == NULL) {
        /* Failed to allocate memory */
        return ESP_ERR_HTTPD_ALLOC_MEM;
    }

    if (httpd_server_init(hd) != ESP_OK) {
        httpd_delete(hd);
        return ESP_FAIL;
    }

    httpd_sess_init(hd);
    if (httpd_os_thread_create(&hd->hd_td.handle, "httpd",
                               hd->config.stack_size,
                               hd->config.task_priority,
                               httpd_thread, hd,
                               hd->config.core_id) != ESP_OK) {
        /* Failed to launch task */
        httpd_delete(hd);
        return ESP_ERR_HTTPD_TASK;
    }

    *handle = (httpd_handle_t *)hd;
    return ESP_OK;
}