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
struct sock_db {int /*<<< orphan*/  lru_counter; } ;
struct httpd_data {int dummy; } ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ httpd_req_delete (struct httpd_data*) ; 
 scalar_t__ httpd_req_new (struct httpd_data*,struct sock_db*) ; 
 struct sock_db* httpd_sess_get (struct httpd_data*,int) ; 
 int /*<<< orphan*/  httpd_sess_get_lru_counter () ; 

esp_err_t httpd_sess_process(struct httpd_data *hd, int newfd)
{
    struct sock_db *sd = httpd_sess_get(hd, newfd);
    if (! sd) {
        return ESP_FAIL;
    }

    ESP_LOGD(TAG, LOG_FMT("httpd_req_new"));
    if (httpd_req_new(hd, sd) != ESP_OK) {
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, LOG_FMT("httpd_req_delete"));
    if (httpd_req_delete(hd) != ESP_OK) {
        return ESP_FAIL;
    }
    ESP_LOGD(TAG, LOG_FMT("success"));
    sd->lru_counter = httpd_sess_get_lru_counter();
    return ESP_OK;
}