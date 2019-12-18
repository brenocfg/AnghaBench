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

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int errno ; 
 int /*<<< orphan*/  strerror (int) ; 

int iperf_show_socket_error_reason(const char *str, int sockfd)
{
    int err = errno;
    if (err != 0) {
        ESP_LOGW(TAG, "%s error, error code: %d, reason: %s", str, err, strerror(err));
    }

    return err;
}