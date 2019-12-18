#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/ * username; } ;
struct TYPE_5__ {TYPE_1__ connection_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

esp_err_t esp_http_client_set_username(esp_http_client_handle_t client, const char *username)
{
    if (client == NULL) {
        ESP_LOGE(TAG, "client must not be NULL");
        return ESP_ERR_INVALID_ARG;
    }
    if (username == NULL && client->connection_info.username != NULL) {
        free(client->connection_info.username);
        client->connection_info.username = NULL;
    } else if (username != NULL) {
        client->connection_info.username = strdup(username);
    }
    return ESP_OK;
}