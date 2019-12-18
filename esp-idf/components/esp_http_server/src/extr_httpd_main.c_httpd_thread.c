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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct httpd_data {TYPE_1__ hd_td; int /*<<< orphan*/  listen_fd; int /*<<< orphan*/  ctrl_fd; int /*<<< orphan*/  msg_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  THREAD_RUNNING ; 
 int /*<<< orphan*/  THREAD_STOPPED ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_free_ctrl_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_close_all_sessions (struct httpd_data*) ; 
 int /*<<< orphan*/  httpd_os_thread_delete () ; 
 int httpd_server (struct httpd_data*) ; 

__attribute__((used)) static void httpd_thread(void *arg)
{
    int ret;
    struct httpd_data *hd = (struct httpd_data *) arg;
    hd->hd_td.status = THREAD_RUNNING;

    ESP_LOGD(TAG, LOG_FMT("web server started"));
    while (1) {
        ret = httpd_server(hd);
        if (ret != ESP_OK) {
            break;
        }
    }

    ESP_LOGD(TAG, LOG_FMT("web server exiting"));
    close(hd->msg_fd);
    cs_free_ctrl_sock(hd->ctrl_fd);
    httpd_close_all_sessions(hd);
    close(hd->listen_fd);
    hd->hd_td.status = THREAD_STOPPED;
    httpd_os_thread_delete();
}