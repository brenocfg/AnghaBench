#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_3__* esp_http_client_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_10__ {int /*<<< orphan*/  nc; scalar_t__ cnonce; int /*<<< orphan*/  uri; } ;
struct TYPE_8__ {scalar_t__ auth_type; int /*<<< orphan*/  password; scalar_t__ username; int /*<<< orphan*/  path; } ;
struct TYPE_9__ {int first_line_prepared; TYPE_4__* auth_data; TYPE_2__ connection_info; int /*<<< orphan*/  parser; TYPE_1__* response; scalar_t__ process_again; } ;
struct TYPE_7__ {scalar_t__ data_process; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ HTTP_AUTH_TYPE_BASIC ; 
 scalar_t__ HTTP_AUTH_TYPE_DIGEST ; 
 int /*<<< orphan*/  HTTP_RESPONSE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_http_client_set_header (TYPE_3__*,char*,char*) ; 
 scalar_t__ esp_random () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* http_auth_basic (scalar_t__,int /*<<< orphan*/ ) ; 
 char* http_auth_digest (scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  http_parser_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t esp_http_client_prepare(esp_http_client_handle_t client)
{
    client->process_again = 0;
    client->response->data_process = 0;
    client->first_line_prepared = false;
    http_parser_init(client->parser, HTTP_RESPONSE);
    if (client->connection_info.username) {
        char *auth_response = NULL;

        if (client->connection_info.auth_type == HTTP_AUTH_TYPE_BASIC) {
            auth_response = http_auth_basic(client->connection_info.username, client->connection_info.password);
        } else if (client->connection_info.auth_type == HTTP_AUTH_TYPE_DIGEST && client->auth_data) {
            client->auth_data->uri = client->connection_info.path;
            client->auth_data->cnonce = ((uint64_t)esp_random() << 32) + esp_random();
            auth_response = http_auth_digest(client->connection_info.username, client->connection_info.password, client->auth_data);
            client->auth_data->nc ++;
        }

        if (auth_response) {
            ESP_LOGD(TAG, "auth_response=%s", auth_response);
            esp_http_client_set_header(client, "Authorization", auth_response);
            free(auth_response);
        }
    }
    return ESP_OK;
}