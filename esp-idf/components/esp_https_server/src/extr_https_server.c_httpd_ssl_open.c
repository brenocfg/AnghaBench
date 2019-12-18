#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_tls_t ;
typedef  int /*<<< orphan*/  esp_tls_cfg_server_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int esp_tls_server_session_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_tls_server_session_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * httpd_get_global_transport_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpd_sess_set_pending_override (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_sess_set_recv_override (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_sess_set_send_override (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_sess_set_transport_ctx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_ssl_close ; 
 int /*<<< orphan*/  httpd_ssl_pending ; 
 int /*<<< orphan*/  httpd_ssl_recv ; 
 int /*<<< orphan*/  httpd_ssl_send ; 

__attribute__((used)) static esp_err_t httpd_ssl_open(httpd_handle_t server, int sockfd)
{
    assert(server != NULL);

    // Retrieve the SSL context from the global context field (set in config)
    esp_tls_cfg_server_t *global_ctx = httpd_get_global_transport_ctx(server);
    assert(global_ctx != NULL);

    esp_tls_t *tls = (esp_tls_t *)calloc(1, sizeof(esp_tls_t));
    if (!tls) {
        return ESP_ERR_NO_MEM;
    }
    ESP_LOGI(TAG, "performing session handshake");
    int ret = esp_tls_server_session_create(global_ctx, sockfd, tls);
    if (ret != 0) {
        ESP_LOGE(TAG, "esp_tls_create_server_session failed");
        goto fail;
    }

    // Store the SSL session into the context field of the HTTPD session object
    httpd_sess_set_transport_ctx(server, sockfd, tls, httpd_ssl_close);

    // Set rx/tx/pending override functions
    httpd_sess_set_send_override(server, sockfd, httpd_ssl_send);
    httpd_sess_set_recv_override(server, sockfd, httpd_ssl_recv);
    httpd_sess_set_pending_override(server, sockfd, httpd_ssl_pending);

    // all access should now go through SSL

    ESP_LOGD(TAG, "Secure socket open");

    return ESP_OK;
fail:
    esp_tls_server_session_delete(tls);
    return ESP_FAIL;
}