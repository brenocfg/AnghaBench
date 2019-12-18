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
typedef  TYPE_3__* esp_http_client_handle_t ;
struct TYPE_7__ {size_t method; void* auth_type; } ;
struct TYPE_8__ {scalar_t__ state; char* auth_header; int process_again; TYPE_2__ connection_info; TYPE_1__* auth_data; int /*<<< orphan*/  redirect_counter; } ;
struct TYPE_6__ {int nc; void* opaque; void* nonce; void* qop; void* algorithm; void* realm; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 void* HTTP_AUTH_TYPE_BASIC ; 
 void* HTTP_AUTH_TYPE_DIGEST ; 
 void* HTTP_AUTH_TYPE_NONE ; 
 int /*<<< orphan*/ * HTTP_METHOD_MAPPING ; 
 scalar_t__ HTTP_STATE_RES_COMPLETE_HEADER ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _clear_auth_data (TYPE_3__*) ; 
 void* http_utils_get_string_between (char*,char*,char*) ; 
 scalar_t__ http_utils_str_starts_with (char*,char*) ; 
 int /*<<< orphan*/  http_utils_trim_whitespace (char**) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

void esp_http_client_add_auth(esp_http_client_handle_t client)
{
    if (client == NULL) {
        return;
    }
    if (client->state != HTTP_STATE_RES_COMPLETE_HEADER) {
        return;
    }

    char *auth_header = client->auth_header;
    if (auth_header) {
        http_utils_trim_whitespace(&auth_header);
        ESP_LOGD(TAG, "UNAUTHORIZED: %s", auth_header);
        client->redirect_counter++;
        if (http_utils_str_starts_with(auth_header, "Digest") == 0) {
            ESP_LOGD(TAG, "type = Digest");
            client->connection_info.auth_type = HTTP_AUTH_TYPE_DIGEST;
#ifdef CONFIG_ESP_HTTP_CLIENT_ENABLE_BASIC_AUTH
        } else if (http_utils_str_starts_with(auth_header, "Basic") == 0) {
            ESP_LOGD(TAG, "type = Basic");
            client->connection_info.auth_type = HTTP_AUTH_TYPE_BASIC;
#endif
        } else {
            client->connection_info.auth_type = HTTP_AUTH_TYPE_NONE;
            ESP_LOGE(TAG, "This authentication method is not supported: %s", auth_header);
            return;
        }

        _clear_auth_data(client);

        client->auth_data->method = strdup(HTTP_METHOD_MAPPING[client->connection_info.method]);

        client->auth_data->nc = 1;
        client->auth_data->realm = http_utils_get_string_between(auth_header, "realm=\"", "\"");
        client->auth_data->algorithm = http_utils_get_string_between(auth_header, "algorithm=", ",");
        client->auth_data->qop = http_utils_get_string_between(auth_header, "qop=\"", "\"");
        client->auth_data->nonce = http_utils_get_string_between(auth_header, "nonce=\"", "\"");
        client->auth_data->opaque = http_utils_get_string_between(auth_header, "opaque=\"", "\"");
        client->process_again = 1;
    } else {
        client->connection_info.auth_type = HTTP_AUTH_TYPE_NONE;
        ESP_LOGW(TAG, "This request requires authentication, but does not provide header information for that");
    }
}