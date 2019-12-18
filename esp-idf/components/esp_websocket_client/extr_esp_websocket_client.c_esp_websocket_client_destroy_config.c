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
struct TYPE_6__ {struct TYPE_6__* subprotocol; struct TYPE_6__* password; struct TYPE_6__* username; struct TYPE_6__* scheme; struct TYPE_6__* path; struct TYPE_6__* uri; struct TYPE_6__* host; } ;
typedef  TYPE_1__ websocket_config_storage_t ;
typedef  TYPE_2__* esp_websocket_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {TYPE_1__* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t esp_websocket_client_destroy_config(esp_websocket_client_handle_t client)
{
    if (client == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    websocket_config_storage_t *cfg = client->config;
    if (client->config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    free(cfg->host);
    free(cfg->uri);
    free(cfg->path);
    free(cfg->scheme);
    free(cfg->username);
    free(cfg->password);
    free(cfg->subprotocol);
    memset(cfg, 0, sizeof(websocket_config_storage_t));
    free(client->config);
    client->config = NULL;
    return ESP_OK;
}