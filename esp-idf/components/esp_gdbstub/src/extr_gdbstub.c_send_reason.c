#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_gdbstub_send_char (char) ; 
 int /*<<< orphan*/  esp_gdbstub_send_end () ; 
 int /*<<< orphan*/  esp_gdbstub_send_hex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_gdbstub_send_start () ; 
 TYPE_1__ s_scratch ; 

__attribute__((used)) static void send_reason(void)
{
    esp_gdbstub_send_start();
    esp_gdbstub_send_char('T');
    esp_gdbstub_send_hex(s_scratch.signal, 8);
    esp_gdbstub_send_end();
}