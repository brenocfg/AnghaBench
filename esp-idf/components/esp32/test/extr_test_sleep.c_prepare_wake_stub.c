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
 int /*<<< orphan*/  esp_deep_sleep_start () ; 
 int /*<<< orphan*/  esp_set_deep_sleep_wake_stub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_sleep_enable_timer_wakeup (int) ; 
 int /*<<< orphan*/  wake_stub ; 

__attribute__((used)) static void prepare_wake_stub(void)
{
    esp_set_deep_sleep_wake_stub(&wake_stub);
    esp_sleep_enable_timer_wakeup(100000);
    esp_deep_sleep_start();
}