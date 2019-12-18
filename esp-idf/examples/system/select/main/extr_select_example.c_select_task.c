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
struct timeval {int tv_sec; int /*<<< orphan*/  tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  check_and_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errno ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  socket_fd ; 
 int /*<<< orphan*/  uart_fd ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void select_task(void *param)
{
    while (1) {
        int s;
        fd_set rfds;
        struct timeval tv = {
            .tv_sec = 1,
            .tv_usec = 0,
        };

        FD_ZERO(&rfds);
        FD_SET(uart_fd, &rfds);
        FD_SET(socket_fd, &rfds);

        s = select(MAX(uart_fd, socket_fd) + 1, &rfds, NULL, NULL, &tv);

        if (s < 0) {
            ESP_LOGE(TAG, "Select failed: errno %d", errno);
        } else if (s == 0) {
            ESP_LOGI(TAG, "Timeout has been reached and nothing has been received");
        } else {
            check_and_print(socket_fd, &rfds, "socket");
            check_and_print(uart_fd, &rfds, "UART1");
        }
    }

    vTaskDelete(NULL);
}