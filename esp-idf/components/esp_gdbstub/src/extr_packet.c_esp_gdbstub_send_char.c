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
 char s_chsum ; 

void esp_gdbstub_send_char(char c)
{
    if (c == '#' || c == '$' || c == '}' || c == '*') {
        esp_gdbstub_putchar('}');
        esp_gdbstub_putchar(c ^ 0x20);
        s_chsum += (c ^ 0x20) + '}';
    } else {
        esp_gdbstub_putchar(c);
        s_chsum += c;
    }
}