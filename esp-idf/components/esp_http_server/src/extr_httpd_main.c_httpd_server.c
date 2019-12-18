#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; } ;
struct TYPE_3__ {scalar_t__ lru_purge_enable; } ;
struct httpd_data {int listen_fd; int ctrl_fd; TYPE_2__ hd_td; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ THREAD_STOPPING ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ httpd_accept_conn (struct httpd_data*,int) ; 
 scalar_t__ httpd_is_sess_available (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_process_ctrl_msg (struct httpd_data*) ; 
 int httpd_sess_delete (struct httpd_data*,int) ; 
 int /*<<< orphan*/  httpd_sess_delete_invalid (struct httpd_data*) ; 
 int httpd_sess_iterate (struct httpd_data*,int) ; 
 scalar_t__ httpd_sess_pending (struct httpd_data*,int) ; 
 scalar_t__ httpd_sess_process (struct httpd_data*,int) ; 
 int /*<<< orphan*/  httpd_sess_set_descriptors (struct httpd_data*,int /*<<< orphan*/ *,int*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t httpd_server(struct httpd_data *hd)
{
    fd_set read_set;
    FD_ZERO(&read_set);
    if (hd->config.lru_purge_enable || httpd_is_sess_available(hd)) {
        /* Only listen for new connections if server has capacity to
         * handle more (or when LRU purge is enabled, in which case
         * older connections will be closed) */
        FD_SET(hd->listen_fd, &read_set);
    }
    FD_SET(hd->ctrl_fd, &read_set);

    int tmp_max_fd;
    httpd_sess_set_descriptors(hd, &read_set, &tmp_max_fd);
    int maxfd = MAX(hd->listen_fd, tmp_max_fd);
    tmp_max_fd = maxfd;
    maxfd = MAX(hd->ctrl_fd, tmp_max_fd);

    ESP_LOGD(TAG, LOG_FMT("doing select maxfd+1 = %d"), maxfd + 1);
    int active_cnt = select(maxfd + 1, &read_set, NULL, NULL, NULL);
    if (active_cnt < 0) {
        ESP_LOGE(TAG, LOG_FMT("error in select (%d)"), errno);
        httpd_sess_delete_invalid(hd);
        return ESP_OK;
    }

    /* Case0: Do we have a control message? */
    if (FD_ISSET(hd->ctrl_fd, &read_set)) {
        ESP_LOGD(TAG, LOG_FMT("processing ctrl message"));
        httpd_process_ctrl_msg(hd);
        if (hd->hd_td.status == THREAD_STOPPING) {
            ESP_LOGD(TAG, LOG_FMT("stopping thread"));
            return ESP_FAIL;
        }
    }

    /* Case1: Do we have any activity on the current data
     * sessions? */
    int fd = -1;
    while ((fd = httpd_sess_iterate(hd, fd)) != -1) {
        if (FD_ISSET(fd, &read_set) || (httpd_sess_pending(hd, fd))) {
            ESP_LOGD(TAG, LOG_FMT("processing socket %d"), fd);
            if (httpd_sess_process(hd, fd) != ESP_OK) {
                ESP_LOGD(TAG, LOG_FMT("closing socket %d"), fd);
                close(fd);
                /* Delete session and update fd to that
                 * preceding the one being deleted */
                fd = httpd_sess_delete(hd, fd);
            }
        }
    }

    /* Case2: Do we have any incoming connection requests to
     * process? */
    if (FD_ISSET(hd->listen_fd, &read_set)) {
        ESP_LOGD(TAG, LOG_FMT("processing listen socket %d"), hd->listen_fd);
        if (httpd_accept_conn(hd, hd->listen_fd) != ESP_OK) {
            ESP_LOGW(TAG, LOG_FMT("error accepting new connection"));
        }
    }
    return ESP_OK;
}