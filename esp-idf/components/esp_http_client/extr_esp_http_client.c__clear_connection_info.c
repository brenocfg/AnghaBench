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
typedef  TYPE_1__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  connection_info_t ;
struct TYPE_7__ {struct TYPE_7__* url; struct TYPE_7__* scheme; struct TYPE_7__* password; struct TYPE_7__* username; struct TYPE_7__* query; struct TYPE_7__* host; struct TYPE_7__* path; } ;
struct TYPE_6__ {TYPE_2__ connection_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strlen (TYPE_2__*) ; 

__attribute__((used)) static esp_err_t _clear_connection_info(esp_http_client_handle_t client)
{
    free(client->connection_info.path);
    free(client->connection_info.host);
    free(client->connection_info.query);
    free(client->connection_info.username);
    if (client->connection_info.password) {
        memset(client->connection_info.password, 0, strlen(client->connection_info.password));
        free(client->connection_info.password);
    }
    free(client->connection_info.scheme);
    free(client->connection_info.url);
    memset(&client->connection_info, 0, sizeof(connection_info_t));
    return ESP_OK;
}