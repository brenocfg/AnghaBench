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
struct TYPE_3__ {char* command; char* hint; int /*<<< orphan*/ * func; int /*<<< orphan*/ * help; } ;
typedef  TYPE_1__ esp_console_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__ const*) ; 
 int /*<<< orphan*/  make ; 

__attribute__((used)) static void register_make(void)
{
    const esp_console_cmd_t cmd = {
        .command = "make",
        .help = NULL, /* Do not include in 'help' output */
        .hint = "all | flash | monitor",
        .func = &make,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}