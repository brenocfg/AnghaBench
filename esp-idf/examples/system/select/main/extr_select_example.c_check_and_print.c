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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int,char const*,char*) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TAG ; 
 int read (int,char*,int) ; 

__attribute__((used)) static void check_and_print(int fd, const fd_set *rfds, const char *src_msg)
{
    char buf[100];
    int read_bytes;

    if (FD_ISSET(fd, rfds)) {
        if ((read_bytes = read(fd, buf, sizeof(buf)-1)) > 0) {
            buf[read_bytes] = '\0';
            ESP_LOGI(TAG, "%d bytes were received through %s: %s", read_bytes, src_msg, buf);
        } else {
            ESP_LOGE(TAG, "%s read error", src_msg);
        }
    }
}