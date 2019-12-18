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
typedef  intptr_t uint32_t ;

/* Variables and functions */
 intptr_t esp_gdbstub_gethex (unsigned char const**,int) ; 
 int esp_gdbstub_readmem (intptr_t) ; 
 int /*<<< orphan*/  esp_gdbstub_send_end () ; 
 int /*<<< orphan*/  esp_gdbstub_send_hex (int,int) ; 
 int /*<<< orphan*/  esp_gdbstub_send_start () ; 
 int /*<<< orphan*/  esp_gdbstub_send_str_packet (char*) ; 

__attribute__((used)) static void handle_m_command(const unsigned char* cmd, int len)
{
    intptr_t addr = (intptr_t) esp_gdbstub_gethex(&cmd, -1);
    cmd++;
    uint32_t size = esp_gdbstub_gethex(&cmd, -1);

    if (esp_gdbstub_readmem(addr) < 0 || esp_gdbstub_readmem(addr + size - 1) < 0) {
        esp_gdbstub_send_str_packet("E01");
        return;
    }

    esp_gdbstub_send_start();
    for (int i = 0; i < size; ++i) {
        int b = esp_gdbstub_readmem(addr++);
        esp_gdbstub_send_hex(b, 8);
    }
    esp_gdbstub_send_end();
}