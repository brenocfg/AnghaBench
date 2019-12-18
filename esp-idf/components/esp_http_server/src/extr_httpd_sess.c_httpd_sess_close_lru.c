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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int max_open_sockets; } ;
struct httpd_data {TYPE_2__* hd_sd; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int fd; scalar_t__ lru_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  httpd_sess_trigger_close (struct httpd_data*,int) ; 

esp_err_t httpd_sess_close_lru(struct httpd_data *hd)
{
    uint64_t lru_counter = UINT64_MAX;
    int lru_fd = -1;
    int i;
    for (i = 0; i < hd->config.max_open_sockets; i++) {
        /* If a descriptor is -1, there is no need to close any session.
         * So, we can return from here, without finding the Least Recently Used
         * session
         */
        if (hd->hd_sd[i].fd == -1) {
            return ESP_OK;
        }
        if (hd->hd_sd[i].lru_counter < lru_counter) {
            lru_counter = hd->hd_sd[i].lru_counter;
            lru_fd = hd->hd_sd[i].fd;
        }
    }
    ESP_LOGD(TAG, LOG_FMT("fd = %d"), lru_fd);
    return httpd_sess_trigger_close(hd, lru_fd);
}