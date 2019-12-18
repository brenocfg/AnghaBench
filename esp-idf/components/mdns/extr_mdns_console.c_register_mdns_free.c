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
struct TYPE_3__ {char* command; char* help; int /*<<< orphan*/ * argtable; int /*<<< orphan*/ * func; int /*<<< orphan*/ * hint; } ;
typedef  TYPE_1__ esp_console_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_mdns_free ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__ const*) ; 

__attribute__((used)) static void register_mdns_free(void)
{
    const esp_console_cmd_t cmd_free = {
        .command = "mdns_free",
        .help = "Stop MDNS Server",
        .hint = NULL,
        .func = &cmd_mdns_free,
        .argtable = NULL
    };

    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd_free) );
}