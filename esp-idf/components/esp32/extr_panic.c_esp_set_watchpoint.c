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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 

esp_err_t esp_set_watchpoint(int no, void *adr, int size, int flags)
{
    int x;
    if (no < 0 || no > 1) {
        return ESP_ERR_INVALID_ARG;
    }
    if (flags & (~0xC0000000)) {
        return ESP_ERR_INVALID_ARG;
    }
    int dbreakc = 0x3F;
    //We support watching 2^n byte values, from 1 to 64. Calculate the mask for that.
    for (x = 0; x < 7; x++) {
        if (size == (1 << x)) {
            break;
        }
        dbreakc <<= 1;
    }
    if (x == 7) {
        return ESP_ERR_INVALID_ARG;
    }
    //Mask mask and add in flags.
    dbreakc = (dbreakc & 0x3f) | flags;

    if (no == 0) {
        asm volatile(
            "wsr.dbreaka0 %0\n" \
            "wsr.dbreakc0 %1\n" \
            ::"r"(adr), "r"(dbreakc));
    } else {
        asm volatile(
            "wsr.dbreaka1 %0\n" \
            "wsr.dbreakc1 %1\n" \
            ::"r"(adr), "r"(dbreakc));
    }
    return ESP_OK;
}