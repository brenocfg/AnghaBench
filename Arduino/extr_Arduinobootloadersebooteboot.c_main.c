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
struct eboot_command {scalar_t__ action; scalar_t__* args; } ;

/* Variables and functions */
 scalar_t__ ACTION_COPY_RAW ; 
 scalar_t__ ACTION_LOAD_APP ; 
 int /*<<< orphan*/  SWRST ; 
 int copy_raw (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  eboot_command_clear () ; 
 scalar_t__ eboot_command_read (struct eboot_command*) ; 
 int /*<<< orphan*/  ets_putc (char) ; 
 int /*<<< orphan*/  ets_wdt_disable () ; 
 int /*<<< orphan*/  ets_wdt_enable () ; 
 int load_app_from_flash_raw (scalar_t__) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ ) ; 

void main()
{
    int res = 9;
    struct eboot_command cmd;
    
    print_version(0);

    if (eboot_command_read(&cmd) == 0) {
        // valid command was passed via RTC_MEM
        eboot_command_clear();
        ets_putc('@');
    } else {
        // no valid command found
        cmd.action = ACTION_LOAD_APP;
        cmd.args[0] = 0;
        ets_putc('~');
    }

    if (cmd.action == ACTION_COPY_RAW) {
        ets_putc('c'); ets_putc('p'); ets_putc(':');
        ets_wdt_disable();
        res = copy_raw(cmd.args[0], cmd.args[1], cmd.args[2]);
        ets_wdt_enable();
        ets_putc('0'+res); ets_putc('\n');
        if (res == 0) {
            cmd.action = ACTION_LOAD_APP;
            cmd.args[0] = cmd.args[1];
        }
    }

    if (cmd.action == ACTION_LOAD_APP) {
        ets_putc('l'); ets_putc('d'); ets_putc('\n');
        res = load_app_from_flash_raw(cmd.args[0]);
        //we will get to this only on load fail
        ets_putc('e'); ets_putc(':'); ets_putc('0'+res); ets_putc('\n');
    }

    if (res) {
        SWRST;
    }

    while(true){}
}