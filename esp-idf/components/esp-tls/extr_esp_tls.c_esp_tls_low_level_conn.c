#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_11__ {int conn_state; int sockfd; int is_tls; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  error_handle; int /*<<< orphan*/  wset; int /*<<< orphan*/  rset; int /*<<< orphan*/  server_fd; } ;
typedef  TYPE_1__ esp_tls_t ;
struct TYPE_12__ {int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  non_block; } ;
typedef  TYPE_2__ esp_tls_cfg_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  error ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_ESP ; 
 int /*<<< orphan*/  ERR_TYPE_SYSTEM ; 
 int /*<<< orphan*/  ESP_ERR_ESP_TLS_SOCKET_SETOPT_FAILED ; 
 int /*<<< orphan*/  ESP_INT_EVENT_TRACKER_CAPTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
#define  ESP_TLS_CONNECTING 131 
#define  ESP_TLS_FAIL 130 
#define  ESP_TLS_HANDSHAKE 129 
#define  ESP_TLS_INIT 128 
 int /*<<< orphan*/  FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _esp_tls_read ; 
 int /*<<< orphan*/  _esp_tls_write ; 
 int /*<<< orphan*/  create_ssl_handle (char const*,int,TYPE_2__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  esp_tcp_connect (char const*,int,int,int*,TYPE_1__*,TYPE_2__ const*) ; 
 int esp_tls_handshake (TYPE_1__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned int*) ; 
 int /*<<< orphan*/  mbedtls_net_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ms_to_timeval (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  tcp_read ; 
 int /*<<< orphan*/  tcp_write ; 

__attribute__((used)) static int esp_tls_low_level_conn(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg, esp_tls_t *tls)
{
    if (!tls) {
        ESP_LOGE(TAG, "empty esp_tls parameter");
        return -1;
    }
    esp_err_t esp_ret;
    /* These states are used to keep a tab on connection progress in case of non-blocking connect,
    and in case of blocking connect these cases will get executed one after the other */
    switch (tls->conn_state) {
    case ESP_TLS_INIT:
        tls->sockfd = -1;
        if (cfg != NULL) {
#ifdef CONFIG_ESP_TLS_USING_MBEDTLS
            mbedtls_net_init(&tls->server_fd);
#endif
            tls->is_tls = true;
        }
        if ((esp_ret = esp_tcp_connect(hostname, hostlen, port, &tls->sockfd, tls, cfg)) != ESP_OK) {
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_ESP, esp_ret);
            return -1;
        }
        if (!cfg) {
            tls->read = tcp_read;
            tls->write = tcp_write;
            ESP_LOGD(TAG, "non-tls connection established");
            return 1;
        }
        if (cfg->non_block) {
            FD_ZERO(&tls->rset);
            FD_SET(tls->sockfd, &tls->rset);
            tls->wset = tls->rset;
        }
        tls->conn_state = ESP_TLS_CONNECTING;
    /* falls through */
    case ESP_TLS_CONNECTING:
        if (cfg->non_block) {
            ESP_LOGD(TAG, "connecting...");
            struct timeval tv;
            ms_to_timeval(cfg->timeout_ms, &tv);

            /* In case of non-blocking I/O, we use the select() API to check whether
               connection has been estbalished or not*/
            if (select(tls->sockfd + 1, &tls->rset, &tls->wset, NULL,
                       cfg->timeout_ms ? &tv : NULL) == 0) {
                ESP_LOGD(TAG, "select() timed out");
                return 0;
            }
            if (FD_ISSET(tls->sockfd, &tls->rset) || FD_ISSET(tls->sockfd, &tls->wset)) {
                int error;
                unsigned int len = sizeof(error);
                /* pending error check */
                if (getsockopt(tls->sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
                    ESP_LOGD(TAG, "Non blocking connect failed");
                    ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_SYSTEM, errno);
                    ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_ESP, ESP_ERR_ESP_TLS_SOCKET_SETOPT_FAILED);
                    tls->conn_state = ESP_TLS_FAIL;
                    return -1;
                }
            }
        }
        /* By now, the connection has been established */
        esp_ret = create_ssl_handle(hostname, hostlen, cfg, tls);
        if (esp_ret != ESP_OK) {
            ESP_LOGE(TAG, "create_ssl_handle failed");
            ESP_INT_EVENT_TRACKER_CAPTURE(tls->error_handle, ERR_TYPE_ESP, esp_ret);
            tls->conn_state = ESP_TLS_FAIL;
            return -1;
        }
        tls->read = _esp_tls_read;
        tls->write = _esp_tls_write;
        tls->conn_state = ESP_TLS_HANDSHAKE;
    /* falls through */
    case ESP_TLS_HANDSHAKE:
        ESP_LOGD(TAG, "handshake in progress...");
        return esp_tls_handshake(tls, cfg);
        break;
    case ESP_TLS_FAIL:
        ESP_LOGE(TAG, "failed to open a new connection");;
        break;
    default:
        ESP_LOGE(TAG, "invalid esp-tls state");
        break;
    }
    return -1;
}