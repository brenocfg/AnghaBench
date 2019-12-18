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
typedef  scalar_t__ esp_reset_reason_t ;

/* Variables and functions */
 scalar_t__ ESP_RST_UNKNOWN ; 
 int /*<<< orphan*/  PRO_CPU_NUM ; 
 int /*<<< orphan*/  esp_reset_reason_clear_hint () ; 
 scalar_t__ esp_reset_reason_get_hint () ; 
 int /*<<< orphan*/  get_reset_reason (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtc_get_reset_reason (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_reset_reason ; 

__attribute__((used)) static void __attribute__((constructor)) esp_reset_reason_init(void)
{
    esp_reset_reason_t hint = esp_reset_reason_get_hint();
    s_reset_reason = get_reset_reason(rtc_get_reset_reason(PRO_CPU_NUM),
                                      hint);
    if (hint != ESP_RST_UNKNOWN) {
        esp_reset_reason_clear_hint();
    }
}