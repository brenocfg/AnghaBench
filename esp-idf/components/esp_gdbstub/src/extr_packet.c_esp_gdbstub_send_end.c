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
 int /*<<< orphan*/  esp_gdbstub_putchar (char) ; 
 int /*<<< orphan*/  esp_gdbstub_send_hex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_chsum ; 

void esp_gdbstub_send_end(void)
{
    esp_gdbstub_putchar('#');
    esp_gdbstub_send_hex(s_chsum, 8);
}