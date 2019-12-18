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
 int /*<<< orphan*/  esp_gdbstub_send_end () ; 
 int /*<<< orphan*/  esp_gdbstub_send_start () ; 
 int /*<<< orphan*/  esp_gdbstub_send_str (char const*) ; 

void esp_gdbstub_send_str_packet(const char* str)
{
    esp_gdbstub_send_start();
    if (str != NULL) {
        esp_gdbstub_send_str(str);
    }
    esp_gdbstub_send_end();
}