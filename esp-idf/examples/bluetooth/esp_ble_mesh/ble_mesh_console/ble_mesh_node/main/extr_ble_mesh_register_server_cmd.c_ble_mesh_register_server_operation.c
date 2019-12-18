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
struct TYPE_5__ {int /*<<< orphan*/  end; void* role; void* model; void* opcode; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_end (int) ; 
 void* arg_int1 (char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  arg_str1 (char*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ble_mesh_module_publish_message ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__ const*) ; 
 TYPE_2__ msg_publish ; 

void ble_mesh_register_server_operation(void)
{
    msg_publish.data = arg_str1("d", NULL, "<data>", "message data");
    msg_publish.opcode = arg_int1("o", NULL, "<opcode>", "operation opcode");
    msg_publish.model = arg_int1("m", NULL, "<module>", "module published to");
    msg_publish.role = arg_int1("r", NULL, "<role>", "device role");
    msg_publish.end = arg_end(1);

    const esp_console_cmd_t msg_publish_cmd = {
        .command = "bmpublish",
        .help = "ble mesh: publish message",
        .hint = NULL,
        .func = &ble_mesh_module_publish_message,
        .argtable = &msg_publish,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&msg_publish_cmd));
}