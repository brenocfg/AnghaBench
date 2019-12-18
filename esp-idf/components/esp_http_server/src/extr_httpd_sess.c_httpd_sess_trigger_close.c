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
struct sock_db {int dummy; } ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  httpd_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock_db*) ; 
 int /*<<< orphan*/  httpd_sess_close ; 
 struct sock_db* httpd_sess_get (int /*<<< orphan*/ ,int) ; 

esp_err_t httpd_sess_trigger_close(httpd_handle_t handle, int sockfd)
{
    struct sock_db *sock_db = httpd_sess_get(handle, sockfd);
    if (sock_db) {
        return httpd_queue_work(handle, httpd_sess_close, sock_db);
    }

    return ESP_ERR_NOT_FOUND;
}