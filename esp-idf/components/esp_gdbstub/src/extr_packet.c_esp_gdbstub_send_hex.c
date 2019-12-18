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
 int /*<<< orphan*/  esp_gdbstub_send_char (char const) ; 

void esp_gdbstub_send_hex(int val, int bits)
{
    const char* hex_chars = "0123456789abcdef";
    for (int i = bits; i > 0; i -= 4) {
        esp_gdbstub_send_char(hex_chars[(val >> (i - 4)) & 0xf]);
    }
}