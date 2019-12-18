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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  regfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  esp_gdbstub_send_end () ; 
 int /*<<< orphan*/  esp_gdbstub_send_hex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_gdbstub_send_start () ; 
 int /*<<< orphan*/  gdbstub_hton (int /*<<< orphan*/ ) ; 
 TYPE_1__ s_scratch ; 

__attribute__((used)) static void handle_g_command(const unsigned char* cmd, int len)
{
    uint32_t *p = (uint32_t *) &s_scratch.regfile;
    esp_gdbstub_send_start();
    for (int i = 0; i < sizeof(s_scratch.regfile) / sizeof(*p); ++i) {
        esp_gdbstub_send_hex(gdbstub_hton(*p++), 32);
    }
    esp_gdbstub_send_end();
}