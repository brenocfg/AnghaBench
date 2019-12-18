#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  remove_endpoint; int /*<<< orphan*/  add_endpoint; scalar_t__ priv; } ;
typedef  TYPE_3__ protocomm_t ;
struct TYPE_11__ {int /*<<< orphan*/  task_priority; int /*<<< orphan*/  stack_size; int /*<<< orphan*/  port; } ;
struct TYPE_12__ {TYPE_1__ config; scalar_t__ handle; } ;
struct TYPE_14__ {TYPE_2__ data; scalar_t__ ext_handle_provided; } ;
typedef  TYPE_4__ protocomm_httpd_config_t ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
struct TYPE_15__ {int lru_purge_enable; int max_open_sockets; int /*<<< orphan*/  task_priority; int /*<<< orphan*/  stack_size; int /*<<< orphan*/  server_port; } ;
typedef  TYPE_5__ httpd_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__ HTTPD_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  PROTOCOMM_NO_SESSION_ID ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  httpd_start (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int pc_ext_httpd_handle_provided ; 
 TYPE_3__* pc_httpd ; 
 int /*<<< orphan*/  protocomm_httpd_add_endpoint ; 
 int /*<<< orphan*/  protocomm_httpd_remove_endpoint ; 
 int /*<<< orphan*/  session_id ; 

esp_err_t protocomm_httpd_start(protocomm_t *pc, const protocomm_httpd_config_t *config)
{
    if (!pc || !config) {
        return ESP_ERR_INVALID_ARG;
    }

    if (pc_httpd) {
        if (pc == pc_httpd) {
            ESP_LOGE(TAG, "HTTP server already running for this protocomm instance");
            return ESP_ERR_INVALID_STATE;
        }
        ESP_LOGE(TAG, "HTTP server started for another protocomm instance");
        return ESP_ERR_NOT_SUPPORTED;
    }

    if (config->ext_handle_provided) {
        if (config->data.handle) {
            pc->priv = config->data.handle;
            pc_ext_httpd_handle_provided = true;
        } else {
            return ESP_ERR_INVALID_ARG;
        }
    } else {
        /* Private data will point to the HTTP server handle */
        pc->priv = calloc(1, sizeof(httpd_handle_t));
        if (!pc->priv) {
            ESP_LOGE(TAG, "Malloc failed for HTTP server handle");
            return ESP_ERR_NO_MEM;
        }

        /* Configure the HTTP server */
        httpd_config_t server_config   = HTTPD_DEFAULT_CONFIG();
        server_config.server_port      = config->data.config.port;
        server_config.stack_size       = config->data.config.stack_size;
        server_config.task_priority    = config->data.config.task_priority;
        server_config.lru_purge_enable = true;
        server_config.max_open_sockets = 1;

        esp_err_t err;
        if ((err = httpd_start((httpd_handle_t *)pc->priv, &server_config)) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to start http server: %s", esp_err_to_name(err));
            free(pc->priv);
            return err;
        }
    }
    pc->add_endpoint    = protocomm_httpd_add_endpoint;
    pc->remove_endpoint = protocomm_httpd_remove_endpoint;
    pc_httpd = pc;
    session_id = PROTOCOMM_NO_SESSION_ID;
    return ESP_OK;
}