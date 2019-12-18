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
typedef  TYPE_1__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_http_auth_data_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  nonce; int /*<<< orphan*/  qop; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  realm; int /*<<< orphan*/  method; } ;
struct TYPE_4__ {TYPE_2__* auth_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t _clear_auth_data(esp_http_client_handle_t client)
{
    if (client->auth_data == NULL) {
        return ESP_FAIL;
    }

    free(client->auth_data->method);
    free(client->auth_data->realm);
    free(client->auth_data->algorithm);
    free(client->auth_data->qop);
    free(client->auth_data->nonce);
    free(client->auth_data->opaque);
    memset(client->auth_data, 0, sizeof(esp_http_auth_data_t));
    return ESP_OK;
}