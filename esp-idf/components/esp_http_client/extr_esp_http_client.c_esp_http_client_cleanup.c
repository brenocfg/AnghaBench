#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {struct TYPE_7__* auth_header; struct TYPE_7__* location; struct TYPE_7__* current_header_key; struct TYPE_7__* auth_data; struct TYPE_7__* parser_settings; struct TYPE_7__* parser; struct TYPE_7__* response; struct TYPE_7__* buffer; struct TYPE_7__* data; int /*<<< orphan*/  headers; struct TYPE_7__* request; int /*<<< orphan*/  transport_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  _clear_auth_data (TYPE_1__*) ; 
 int /*<<< orphan*/  _clear_connection_info (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_http_client_close (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_transport_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  http_header_destroy (int /*<<< orphan*/ ) ; 

esp_err_t esp_http_client_cleanup(esp_http_client_handle_t client)
{
    if (client == NULL) {
        return ESP_FAIL;
    }
    esp_http_client_close(client);
    esp_transport_list_destroy(client->transport_list);
    http_header_destroy(client->request->headers);
    free(client->request->buffer->data);
    free(client->request->buffer);
    free(client->request);
    http_header_destroy(client->response->headers);
    free(client->response->buffer->data);
    free(client->response->buffer);
    free(client->response);

    free(client->parser);
    free(client->parser_settings);
    _clear_connection_info(client);
    _clear_auth_data(client);
    free(client->auth_data);
    free(client->current_header_key);
    free(client->location);
    free(client->auth_header);
    free(client);
    return ESP_OK;
}