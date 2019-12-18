#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* command; char* help; TYPE_2__* argtable; int /*<<< orphan*/ * func; int /*<<< orphan*/ * hint; } ;
typedef  TYPE_1__ esp_console_cmd_t ;
struct TYPE_5__ {int /*<<< orphan*/  end; int /*<<< orphan*/  txt; void* proto; void* service; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_end (int) ; 
 void* arg_str1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  arg_strn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  cmd_mdns_service_txt_replace ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__ const*) ; 
 TYPE_2__ mdns_txt_replace_args ; 

__attribute__((used)) static void register_mdns_service_txt_replace(void)
{
    mdns_txt_replace_args.service = arg_str1(NULL, NULL, "<service>", "MDNS Service");
    mdns_txt_replace_args.proto = arg_str1(NULL, NULL, "<proto>", "IP Protocol");
    mdns_txt_replace_args.txt = arg_strn(NULL, NULL, "item", 0, 30, "TXT Items (name=value)");
    mdns_txt_replace_args.end = arg_end(2);

    const esp_console_cmd_t cmd_txt_set = {
        .command = "mdns_service_txt_replace",
        .help = "Replace MDNS service TXT items",
        .hint = NULL,
        .func = &cmd_mdns_service_txt_replace,
        .argtable = &mdns_txt_replace_args
    };

    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd_txt_set) );
}