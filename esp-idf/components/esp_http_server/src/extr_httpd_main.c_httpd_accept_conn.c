#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tv ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int lru_purge_enable; int /*<<< orphan*/  send_wait_timeout; int /*<<< orphan*/  recv_wait_timeout; } ;
struct httpd_data {TYPE_1__ config; } ;
typedef  int socklen_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  addr_from ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  TAG ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  httpd_is_sess_available (struct httpd_data*) ; 
 scalar_t__ httpd_sess_close_lru (struct httpd_data*) ; 
 scalar_t__ httpd_sess_new (struct httpd_data*,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static esp_err_t httpd_accept_conn(struct httpd_data *hd, int listen_fd)
{
    /* If no space is available for new session, close the least recently used one */
    if (hd->config.lru_purge_enable == true) {
        if (!httpd_is_sess_available(hd)) {
            /* Queue asynchronous closure of the least recently used session */
            return httpd_sess_close_lru(hd);
            /* Returning from this allowes the main server thread to process
             * the queued asynchronous control message for closing LRU session.
             * Since connection request hasn't been addressed yet using accept()
             * therefore httpd_accept_conn() will be called again, but this time
             * with space available for one session
             */
       }
    }

    struct sockaddr_in addr_from;
    socklen_t addr_from_len = sizeof(addr_from);
    int new_fd = accept(listen_fd, (struct sockaddr *)&addr_from, &addr_from_len);
    if (new_fd < 0) {
        ESP_LOGW(TAG, LOG_FMT("error in accept (%d)"), errno);
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, LOG_FMT("newfd = %d"), new_fd);

    struct timeval tv;
    /* Set recv timeout of this fd as per config */
    tv.tv_sec = hd->config.recv_wait_timeout;
    tv.tv_usec = 0;
    setsockopt(new_fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    /* Set send timeout of this fd as per config */
    tv.tv_sec = hd->config.send_wait_timeout;
    tv.tv_usec = 0;
    setsockopt(new_fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof(tv));

    if (ESP_OK != httpd_sess_new(hd, new_fd)) {
        ESP_LOGW(TAG, LOG_FMT("session creation failed"));
        close(new_fd);
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, LOG_FMT("complete"));
    return ESP_OK;
}