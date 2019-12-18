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

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 

void bootloader_debug_buffer(const void *buffer, size_t length, const char *label)
{
#if BOOT_LOG_LEVEL >= LOG_LEVEL_DEBUG
    assert(length <= 128); // Avoid unbounded VLA size
    const uint8_t *bytes = (const uint8_t *)buffer;
    char hexbuf[length * 2 + 1];
    hexbuf[length * 2] = 0;
    for (int i = 0; i < length; i++) {
        for (int shift = 0; shift < 2; shift++) {
            uint8_t nibble = (bytes[i] >> (shift ? 0 : 4)) & 0x0F;
            if (nibble < 10) {
                hexbuf[i * 2 + shift] = '0' + nibble;
            } else {
                hexbuf[i * 2 + shift] = 'a' + nibble - 10;
            }
        }
    }
    ESP_LOGD(TAG, "%s: %s", label, hexbuf);
#endif
}