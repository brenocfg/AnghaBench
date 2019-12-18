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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNTP_OPMODE_POLL ; 
 int /*<<< orphan*/  SNTP_SYNC_MODE_SMOOTH ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  sntp_init () ; 
 int /*<<< orphan*/  sntp_set_sync_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sntp_set_time_sync_notification_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sntp_setoperatingmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sntp_setservername (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  time_sync_notification_cb ; 

__attribute__((used)) static void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
#ifdef CONFIG_SNTP_TIME_SYNC_METHOD_SMOOTH
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
#endif
    sntp_init();
}