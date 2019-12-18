#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {char* command; char* help; int /*<<< orphan*/ * func; } ;
typedef  TYPE_1__ esp_console_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__*) ; 
 int /*<<< orphan*/  help_command ; 

esp_err_t esp_console_register_help_command(void)
{
    esp_console_cmd_t command = {
        .command = "help",
        .help = "Print the list of registered commands",
        .func = &help_command
    };
    return esp_console_cmd_register(&command);
}