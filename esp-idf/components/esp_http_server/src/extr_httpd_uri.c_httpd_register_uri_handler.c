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
struct TYPE_6__ {int max_uri_handlers; } ;
struct httpd_data {TYPE_3__** hd_calls; TYPE_1__ config; } ;
struct TYPE_7__ {int /*<<< orphan*/ * uri; int /*<<< orphan*/  user_ctx; int /*<<< orphan*/  handler; int /*<<< orphan*/  method; } ;
typedef  TYPE_2__ httpd_uri_t ;
typedef  int /*<<< orphan*/ * httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {int /*<<< orphan*/ * uri; int /*<<< orphan*/  user_ctx; int /*<<< orphan*/  handler; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_HTTPD_ALLOC_MEM ; 
 int /*<<< orphan*/  ESP_ERR_HTTPD_HANDLERS_FULL ; 
 int /*<<< orphan*/  ESP_ERR_HTTPD_HANDLER_EXISTS ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/ * httpd_find_uri_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

esp_err_t httpd_register_uri_handler(httpd_handle_t handle,
                                     const httpd_uri_t *uri_handler)
{
    if (handle == NULL || uri_handler == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    struct httpd_data *hd = (struct httpd_data *) handle;

    /* Make sure another handler with matching URI and method
     * is not already registered. This will also catch cases
     * when a registered URI wildcard pattern already accounts
     * for the new URI being registered */
    if (httpd_find_uri_handler(handle, uri_handler->uri,
                               strlen(uri_handler->uri),
                               uri_handler->method, NULL) != NULL) {
        ESP_LOGW(TAG, LOG_FMT("handler %s with method %d already registered"),
                 uri_handler->uri, uri_handler->method);
        return ESP_ERR_HTTPD_HANDLER_EXISTS;
    }

    for (int i = 0; i < hd->config.max_uri_handlers; i++) {
        if (hd->hd_calls[i] == NULL) {
            hd->hd_calls[i] = malloc(sizeof(httpd_uri_t));
            if (hd->hd_calls[i] == NULL) {
                /* Failed to allocate memory */
                return ESP_ERR_HTTPD_ALLOC_MEM;
            }

            /* Copy URI string */
            hd->hd_calls[i]->uri = strdup(uri_handler->uri);
            if (hd->hd_calls[i]->uri == NULL) {
                /* Failed to allocate memory */
                free(hd->hd_calls[i]);
                return ESP_ERR_HTTPD_ALLOC_MEM;
            }

            /* Copy remaining members */
            hd->hd_calls[i]->method   = uri_handler->method;
            hd->hd_calls[i]->handler  = uri_handler->handler;
            hd->hd_calls[i]->user_ctx = uri_handler->user_ctx;
            ESP_LOGD(TAG, LOG_FMT("[%d] installed %s"), i, uri_handler->uri);
            return ESP_OK;
        }
        ESP_LOGD(TAG, LOG_FMT("[%d] exists %s"), i, hd->hd_calls[i]->uri);
    }
    ESP_LOGW(TAG, LOG_FMT("no slots left for registering handler"));
    return ESP_ERR_HTTPD_HANDLERS_FULL;
}