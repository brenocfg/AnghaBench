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
struct TYPE_3__ {int max_open_sockets; } ;
struct httpd_data {TYPE_2__* hd_sd; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/ * httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int fd; int /*<<< orphan*/  lru_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  httpd_sess_get_lru_counter () ; 

esp_err_t httpd_sess_update_lru_counter(httpd_handle_t handle, int sockfd)
{
    if (handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Search for the socket database entry */
    struct httpd_data *hd = (struct httpd_data *) handle;
    int i;
    for (i = 0; i < hd->config.max_open_sockets; i++) {
        if (hd->hd_sd[i].fd == sockfd) {
            hd->hd_sd[i].lru_counter = httpd_sess_get_lru_counter();
            return ESP_OK;
        }
    }
    return ESP_ERR_NOT_FOUND;
}