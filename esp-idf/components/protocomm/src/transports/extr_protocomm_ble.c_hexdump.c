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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEX_LEVEL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOG_DEBUG ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static void hexdump(const char *msg, uint8_t *buf, int len)
{
    ESP_LOGD(TAG, "%s:", msg);
    ESP_LOG_BUFFER_HEX_LEVEL(TAG, buf, len, ESP_LOG_DEBUG);
}