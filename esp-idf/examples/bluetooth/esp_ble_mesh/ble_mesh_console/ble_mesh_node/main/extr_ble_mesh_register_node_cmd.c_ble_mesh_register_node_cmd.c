#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* command; char* help; TYPE_3__* argtable; int /*<<< orphan*/ * func; int /*<<< orphan*/ * hint; } ;
typedef  TYPE_2__ esp_console_cmd_t ;
struct TYPE_12__ {void* end; void* group_addr; void* app_idx; void* app_key; void* dev_key; void* unicast_addr; void* net_idx; void* net_key; void* tx_sense_power; void* action_type; void* package_num; void* enable; void* bearer; void* dev_uuid; void* pub_config; TYPE_1__* config_index; void* model_type; void* input_actions; void* input_size; void* output_actions; void* output_size; void* static_val_len; void* static_val; } ;
struct TYPE_10__ {scalar_t__* ival; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 void* arg_end (int) ; 
 void* arg_int0 (char*,int /*<<< orphan*/ *,char*,char*) ; 
 void* arg_int1 (char*,int /*<<< orphan*/ *,char*,char*) ; 
 void* arg_str0 (char*,int /*<<< orphan*/ *,char*,char*) ; 
 void* arg_str1 (char*,int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_3__ bearer ; 
 int /*<<< orphan*/  ble_mesh_init ; 
 int /*<<< orphan*/  ble_mesh_load_oob ; 
 int /*<<< orphan*/  ble_mesh_node_enable_bearer ; 
 int /*<<< orphan*/  ble_mesh_node_enter_network_auto ; 
 int /*<<< orphan*/  ble_mesh_node_reset ; 
 int /*<<< orphan*/  ble_mesh_node_statistics_regist ; 
 int /*<<< orphan*/  ble_mesh_power_set ; 
 int /*<<< orphan*/  ble_mesh_register_node_cb ; 
 TYPE_3__ component ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_2__ const*) ; 
 TYPE_3__ node_network_info ; 
 TYPE_3__ node_statistices ; 
 TYPE_3__ oob ; 
 TYPE_3__ power_set ; 

void ble_mesh_register_node_cmd(void)
{
    const esp_console_cmd_t register_cmd = {
        .command  = "bmreg",
        .help = "ble mesh: provisioner/node register callback",
        .hint = NULL,
        .func = &ble_mesh_register_node_cb,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&register_cmd));

    oob.static_val = arg_str0("s", NULL, "<value>", "Static OOB value");
    oob.static_val_len = arg_int0("l", NULL, "<length>", "Static OOB value length");
    oob.output_size = arg_int0("x", NULL, "<size>", "Maximum size of Output OOB");
    oob.output_actions = arg_int0("o", NULL, "<actions>", "Supported Output OOB Actions");
    oob.input_size = arg_int0("y", NULL, "<size>", "Maximum size of Input OOB");
    oob.input_actions = arg_int0("i", NULL, "<actions>", "Supported Input OOB Actions");
    oob.end = arg_end(1);

    const esp_console_cmd_t oob_cmd = {
        .command = "bmoob",
        .help = "ble mesh: provisioner/node config OOB parameters",
        .hint = NULL,
        .func = &ble_mesh_load_oob,
        .argtable = &oob,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oob_cmd) );

    component.model_type = arg_int0("m", NULL, "<model>", "mesh model");
    component.config_index = arg_int0("c", NULL, "<index>", "mesh model op");
    component.config_index->ival[0] = 0; // set default value
    component.pub_config = arg_int0("p", NULL, "<publish>", "publish message buffer");
    component.dev_uuid = arg_str0("d", NULL, "<uuid>", "device uuid");
    component.end = arg_end(1);

    const esp_console_cmd_t model_cmd = {
        .command = "bminit",
        .help = "ble mesh: provisioner/node init",
        .hint = NULL,
        .func = &ble_mesh_init,
        .argtable = &component,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&model_cmd) );

    bearer.bearer = arg_int0("b", NULL, "<bearer>", "supported bearer");
    bearer.enable = arg_int0("e", NULL, "<enable/disable>", "bearers node supported");
    bearer.end = arg_end(1);

    const esp_console_cmd_t bearer_cmd = {
        .command = "bmnbearer",
        .help = "ble mesh node: enable/disable different bearer",
        .hint = NULL,
        .func = &ble_mesh_node_enable_bearer,
        .argtable = &bearer,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&bearer_cmd));

    const esp_console_cmd_t reset_cmd = {
        .command = "bmnreset",
        .help = "ble mesh node: reset",
        .hint = NULL,
        .func = &ble_mesh_node_reset,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&reset_cmd));

    node_statistices.action_type = arg_str1("z", NULL, "<action>", "action type");
    node_statistices.package_num = arg_int0("p", NULL, "<package>", "package number");
    node_statistices.end = arg_end(1);

    const esp_console_cmd_t node_statistices_cmd = {
        .command = "bmsperf",
        .help = "ble mesh server: performance statistics",
        .hint = NULL,
        .func = &ble_mesh_node_statistics_regist,
        .argtable = &node_statistices,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&node_statistices_cmd));

    power_set.action_type = arg_str1("z", NULL, "<action>", "action type");
    power_set.tx_sense_power = arg_int0("t", NULL, "<power>", "tx power or sense");
    power_set.end = arg_end(1);

    const esp_console_cmd_t power_set_cmd = {
        .command = "bmtxpower",
        .help = "ble mesh: set tx power or sense",
        .hint = NULL,
        .func = &ble_mesh_power_set,
        .argtable = &power_set,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&power_set_cmd));

    node_network_info.net_key = arg_str1("k", NULL, "<net key>", "network key");
    node_network_info.net_idx = arg_int1("n", NULL, "<net index>", "network key index");
    node_network_info.unicast_addr = arg_int1("u", NULL, "<unicast address>", "unicast address");
    node_network_info.dev_key = arg_str1("d", NULL, "<device key>", "device key");
    node_network_info.app_key = arg_str1("a", NULL, "<appkey>", "app key");
    node_network_info.app_idx = arg_int1("i", NULL, "<app index>", "appkey index");
    node_network_info.group_addr = arg_int1("g", NULL, "<group address>", "group address");
    node_network_info.end = arg_end(1);

    const esp_console_cmd_t node_network_info_cmd = {
        .command = "bmnnwk",
        .help = "ble mesh node: auto join network",
        .hint = NULL,
        .func = &ble_mesh_node_enter_network_auto,
        .argtable = &node_network_info,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&node_network_info_cmd));
}