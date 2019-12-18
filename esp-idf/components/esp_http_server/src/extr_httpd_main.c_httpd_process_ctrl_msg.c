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
struct httpd_data {TYPE_1__ hd_td; int /*<<< orphan*/  ctrl_fd; } ;
struct httpd_ctrl_data {int hc_msg; int /*<<< orphan*/  hc_work_arg; int /*<<< orphan*/  (* hc_work ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
#define  HTTPD_CTRL_SHUTDOWN 129 
#define  HTTPD_CTRL_WORK 128 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  THREAD_STOPPING ; 
 int /*<<< orphan*/  errno ; 
 int recv (int /*<<< orphan*/ ,struct httpd_ctrl_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void httpd_process_ctrl_msg(struct httpd_data *hd)
{
    struct httpd_ctrl_data msg;
    int ret = recv(hd->ctrl_fd, &msg, sizeof(msg), 0);
    if (ret <= 0) {
        ESP_LOGW(TAG, LOG_FMT("error in recv (%d)"), errno);
        return;
    }
    if (ret != sizeof(msg)) {
        ESP_LOGW(TAG, LOG_FMT("incomplete msg"));
        return;
    }

    switch (msg.hc_msg) {
    case HTTPD_CTRL_WORK:
        if (msg.hc_work) {
            ESP_LOGD(TAG, LOG_FMT("work"));
            (*msg.hc_work)(msg.hc_work_arg);
        }
        break;
    case HTTPD_CTRL_SHUTDOWN:
        ESP_LOGD(TAG, LOG_FMT("shutdown"));
        hd->hd_td.status = THREAD_STOPPING;
        break;
    default:
        break;
    }
}