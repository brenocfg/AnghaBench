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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  esp_fill_random (void*,size_t) ; 

ssize_t getrandom(void *buf, size_t buflen, unsigned int flags)
{
    // Flags are ignored because:
    // - esp_random is non-blocking so it works for both blocking and non-blocking calls,
    // - don't have opportunity so set som other source of entropy.

    ESP_LOGD(TAG, "getrandom(buf=0x%x, buflen=%d, flags=%u)", (int) buf, buflen, flags);

    if (buf == NULL) {
        errno = EFAULT;
        ESP_LOGD(TAG, "getrandom returns -1 (EFAULT)");
        return -1;
    }

    esp_fill_random(buf, buflen);

    ESP_LOGD(TAG, "getrandom returns %d", buflen);
    return buflen;
}