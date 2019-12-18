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
struct sock_db {int /*<<< orphan*/  recv_fn; } ;
typedef  int /*<<< orphan*/  httpd_recv_func_t ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 struct sock_db* httpd_sess_get (int /*<<< orphan*/ ,int) ; 

esp_err_t httpd_sess_set_recv_override(httpd_handle_t hd, int sockfd, httpd_recv_func_t recv_func)
{
    struct sock_db *sess = httpd_sess_get(hd, sockfd);
    if (!sess) {
        return ESP_ERR_INVALID_ARG;
    }
    sess->recv_fn = recv_func;
    return ESP_OK;
}