#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct http_parser_settings {int dummy; } ;
struct http_parser {int dummy; } ;
typedef  int /*<<< orphan*/  esp_transport_handle_t ;
typedef  int /*<<< orphan*/  esp_http_data_t ;
typedef  int /*<<< orphan*/  esp_http_client_t ;
typedef  TYPE_9__* esp_http_client_handle_t ;
struct TYPE_18__ {int use_global_ca_store; int /*<<< orphan*/ * url; int /*<<< orphan*/ * path; int /*<<< orphan*/ * host; scalar_t__ skip_cert_common_name_check; int /*<<< orphan*/  client_key_pem; int /*<<< orphan*/  client_cert_pem; int /*<<< orphan*/  cert_pem; } ;
typedef  TYPE_10__ esp_http_client_config_t ;
typedef  int /*<<< orphan*/  esp_http_buffer_t ;
typedef  int /*<<< orphan*/  esp_http_auth_data_t ;
struct TYPE_26__ {TYPE_9__* client; } ;
struct TYPE_23__ {int /*<<< orphan*/  host; } ;
struct TYPE_27__ {int /*<<< orphan*/  state; TYPE_8__ event; TYPE_7__* parser; TYPE_6__* parser_settings; TYPE_5__ connection_info; int /*<<< orphan*/  buffer_size_rx; TYPE_4__* response; int /*<<< orphan*/  buffer_size_tx; TYPE_2__* request; int /*<<< orphan*/  transport_list; void* auth_data; } ;
struct TYPE_25__ {TYPE_9__* data; } ;
struct TYPE_24__ {int /*<<< orphan*/  on_chunk_complete; int /*<<< orphan*/  on_message_complete; int /*<<< orphan*/  on_body; int /*<<< orphan*/  on_headers_complete; int /*<<< orphan*/  on_header_value; int /*<<< orphan*/  on_header_field; int /*<<< orphan*/  on_status; int /*<<< orphan*/  on_url; int /*<<< orphan*/  on_message_begin; } ;
struct TYPE_22__ {TYPE_3__* buffer; void* headers; } ;
struct TYPE_21__ {void* data; } ;
struct TYPE_20__ {TYPE_1__* buffer; void* headers; } ;
struct TYPE_19__ {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_HTTPS_PORT ; 
 int /*<<< orphan*/  DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  DEFAULT_HTTP_USER_AGENT ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  HTTP_STATE_INIT ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ _set_config (TYPE_9__*,TYPE_10__ const*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  esp_http_client_cleanup (TYPE_9__*) ; 
 scalar_t__ esp_http_client_set_header (TYPE_9__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_http_client_set_url (TYPE_9__*,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_transport_list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esp_transport_list_init () ; 
 scalar_t__ esp_transport_set_default_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_ssl_enable_global_ca_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_ssl_init () ; 
 int /*<<< orphan*/  esp_transport_ssl_set_cert_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_ssl_set_client_cert_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_ssl_set_client_key_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_ssl_skip_common_name_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_transport_tcp_init () ; 
 void* http_header_init () ; 
 int /*<<< orphan*/  http_on_body ; 
 int /*<<< orphan*/  http_on_chunk_complete ; 
 int /*<<< orphan*/  http_on_header_field ; 
 int /*<<< orphan*/  http_on_header_value ; 
 int /*<<< orphan*/  http_on_headers_complete ; 
 int /*<<< orphan*/  http_on_message_begin ; 
 int /*<<< orphan*/  http_on_message_complete ; 
 int /*<<< orphan*/  http_on_status ; 
 int /*<<< orphan*/  http_on_url ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config)
{

    esp_http_client_handle_t client;
    esp_transport_handle_t tcp;
    bool _success;

    _success = (
                   (client                         = calloc(1, sizeof(esp_http_client_t)))           &&
                   (client->parser                 = calloc(1, sizeof(struct http_parser)))          &&
                   (client->parser_settings        = calloc(1, sizeof(struct http_parser_settings))) &&
                   (client->auth_data              = calloc(1, sizeof(esp_http_auth_data_t)))        &&
                   (client->request                = calloc(1, sizeof(esp_http_data_t)))             &&
                   (client->request->headers       = http_header_init())                             &&
                   (client->request->buffer        = calloc(1, sizeof(esp_http_buffer_t)))           &&
                   (client->response               = calloc(1, sizeof(esp_http_data_t)))             &&
                   (client->response->headers      = http_header_init())                             &&
                   (client->response->buffer       = calloc(1, sizeof(esp_http_buffer_t)))
               );

    if (!_success) {
        ESP_LOGE(TAG, "Error allocate memory");
        goto error;
    }

    _success = (
                   (client->transport_list = esp_transport_list_init()) &&
                   (tcp = esp_transport_tcp_init()) &&
                   (esp_transport_set_default_port(tcp, DEFAULT_HTTP_PORT) == ESP_OK) &&
                   (esp_transport_list_add(client->transport_list, tcp, "http") == ESP_OK)
               );
    if (!_success) {
        ESP_LOGE(TAG, "Error initialize transport");
        goto error;
    }
#ifdef CONFIG_ESP_HTTP_CLIENT_ENABLE_HTTPS
    esp_transport_handle_t ssl;
    _success = (
                   (ssl = esp_transport_ssl_init()) &&
                   (esp_transport_set_default_port(ssl, DEFAULT_HTTPS_PORT) == ESP_OK) &&
                   (esp_transport_list_add(client->transport_list, ssl, "https") == ESP_OK)
               );

    if (!_success) {
        ESP_LOGE(TAG, "Error initialize SSL Transport");
        goto error;
    }

    if (config->use_global_ca_store == true) {
        esp_transport_ssl_enable_global_ca_store(ssl);
    } else if (config->cert_pem) {
        esp_transport_ssl_set_cert_data(ssl, config->cert_pem, strlen(config->cert_pem));
    }

    if (config->client_cert_pem) {
        esp_transport_ssl_set_client_cert_data(ssl, config->client_cert_pem, strlen(config->client_cert_pem));
    }

    if (config->client_key_pem) {
        esp_transport_ssl_set_client_key_data(ssl, config->client_key_pem, strlen(config->client_key_pem));
    }

    if (config->skip_cert_common_name_check) {
        esp_transport_ssl_skip_common_name_check(ssl);
    }
#endif

    if (_set_config(client, config) != ESP_OK) {
        ESP_LOGE(TAG, "Error set configurations");
        goto error;
    }
    _success = (
                   (client->request->buffer->data  = malloc(client->buffer_size_tx))  &&
                   (client->response->buffer->data = malloc(client->buffer_size_rx))
               );

    if (!_success) {
        ESP_LOGE(TAG, "Allocation failed");
        goto error;
    }

    if (config->host != NULL && config->path != NULL) {
        _success = (
            (esp_http_client_set_header(client, "User-Agent", DEFAULT_HTTP_USER_AGENT) == ESP_OK) &&
            (esp_http_client_set_header(client, "Host", client->connection_info.host) == ESP_OK)
        );

        if (!_success) {
            ESP_LOGE(TAG, "Error while setting default configurations");
            goto error;
        }
    } else if (config->url != NULL) {
        _success = (
                    (esp_http_client_set_url(client, config->url) == ESP_OK) &&
                    (esp_http_client_set_header(client, "User-Agent", DEFAULT_HTTP_USER_AGENT) == ESP_OK) &&
                    (esp_http_client_set_header(client, "Host", client->connection_info.host) == ESP_OK)
                );

        if (!_success) {
            ESP_LOGE(TAG, "Error while setting default configurations");
            goto error;
        }
    } else {
        ESP_LOGE(TAG, "config should have either URL or host & path");
        goto error;
    }

    client->parser_settings->on_message_begin = http_on_message_begin;
    client->parser_settings->on_url = http_on_url;
    client->parser_settings->on_status = http_on_status;
    client->parser_settings->on_header_field = http_on_header_field;
    client->parser_settings->on_header_value = http_on_header_value;
    client->parser_settings->on_headers_complete = http_on_headers_complete;
    client->parser_settings->on_body = http_on_body;
    client->parser_settings->on_message_complete = http_on_message_complete;
    client->parser_settings->on_chunk_complete = http_on_chunk_complete;
    client->parser->data = client;
    client->event.client = client;

    client->state = HTTP_STATE_INIT;
    return client;
error:
    esp_http_client_cleanup(client);
    return NULL;
}