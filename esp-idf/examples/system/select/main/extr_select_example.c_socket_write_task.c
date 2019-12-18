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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  socket_deinit () ; 
 int /*<<< orphan*/  socket_fd ; 
 int /*<<< orphan*/  socket_init () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_write_task(void *param)
{
    char buf[20];

    socket_init();

    for (uint8_t i = 1;; ++i) {
        vTaskDelay(3000 / portTICK_PERIOD_MS);

        snprintf(buf, sizeof(buf), "Socket message S%d", i);
        int write_bytes = write(socket_fd, buf, strlen(buf));
        if (write_bytes < 0) {
            ESP_LOGE(TAG, "Socket write error");
        } else {
            ESP_LOGI(TAG, "%d bytes were written to socket: %s", write_bytes, buf);
        }
    }

    socket_deinit();
    vTaskDelete(NULL);
}