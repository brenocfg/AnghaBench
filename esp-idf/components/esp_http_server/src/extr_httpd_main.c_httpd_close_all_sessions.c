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
struct httpd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  httpd_sess_delete (struct httpd_data*,int) ; 
 int httpd_sess_iterate (struct httpd_data*,int) ; 

__attribute__((used)) static void httpd_close_all_sessions(struct httpd_data *hd)
{
    int fd = -1;
    while ((fd = httpd_sess_iterate(hd, fd)) != -1) {
        ESP_LOGD(TAG, LOG_FMT("cleaning up socket %d"), fd);
        httpd_sess_delete(hd, fd);
        close(fd);
    }
}