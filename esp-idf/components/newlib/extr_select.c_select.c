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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  TAG ; 
 int esp_vfs_select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  log_fd_set (char*,int /*<<< orphan*/ *) ; 
 int lwip_select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout)
{
#ifdef CONFIG_LWIP_USE_ONLY_LWIP_SELECT
    ESP_LOGD(TAG, "lwip_select starts with nfds = %d", nfds);
    if (timeout) {
        ESP_LOGD(TAG, "timeout is %lds + %ldus", timeout->tv_sec, timeout->tv_usec);
    }
    log_fd_set("readfds", readfds);
    log_fd_set("writefds", writefds);
    log_fd_set("errorfds", errorfds);

    int ret = lwip_select(nfds, readfds, writefds, errorfds, timeout);

    ESP_LOGD(TAG, "lwip_select returns %d", ret);
    log_fd_set("readfds", readfds);
    log_fd_set("writefds", writefds);
    log_fd_set("errorfds", errorfds);

    return ret;
#else
    return esp_vfs_select(nfds, readfds, writefds, errorfds, timeout);
#endif
}