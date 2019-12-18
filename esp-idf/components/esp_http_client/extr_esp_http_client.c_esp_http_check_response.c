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
typedef  TYPE_2__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {scalar_t__ redirect_counter; scalar_t__ max_redirection_count; int process_again; TYPE_1__* response; scalar_t__ disable_auto_redirect; } ;
struct TYPE_6__ {int status_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_HTTP_MAX_REDIRECT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_OK ; 
#define  HttpStatus_Found 130 
#define  HttpStatus_MovedPermanently 129 
#define  HttpStatus_Unauthorized 128 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_http_client_add_auth (TYPE_2__*) ; 
 int /*<<< orphan*/  esp_http_client_set_redirection (TYPE_2__*) ; 

__attribute__((used)) static esp_err_t esp_http_check_response(esp_http_client_handle_t client)
{
    if (client->redirect_counter >= client->max_redirection_count || client->disable_auto_redirect) {
        ESP_LOGE(TAG, "Error, reach max_redirection_count count=%d", client->redirect_counter);
        return ESP_ERR_HTTP_MAX_REDIRECT;
    }
    switch (client->response->status_code) {
        case HttpStatus_MovedPermanently:
        case HttpStatus_Found:
            esp_http_client_set_redirection(client);
            client->redirect_counter ++;
            client->process_again = 1;
            break;
        case HttpStatus_Unauthorized:
            esp_http_client_add_auth(client);
    }
    return ESP_OK;
}