#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* command; char* help; TYPE_2__* argtable; int /*<<< orphan*/ * func; int /*<<< orphan*/ * hint; } ;
typedef  TYPE_1__ esp_console_cmd_t ;
struct TYPE_10__ {void* end; void* type; void* namespace; void* partition; void* key; void* value; } ;

/* Variables and functions */
 char* ARG_TYPE_STR ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 void* arg_end (int) ; 
 void* arg_str0 (char*,char*,char*,char*) ; 
 void* arg_str1 (char*,char*,char*,char*) ; 
 TYPE_2__ erase_all_args ; 
 TYPE_2__ erase_args ; 
 int /*<<< orphan*/  erase_namespace ; 
 int /*<<< orphan*/  erase_value ; 
 int /*<<< orphan*/  esp_console_cmd_register (TYPE_1__ const*) ; 
 TYPE_2__ get_args ; 
 int /*<<< orphan*/  get_value ; 
 TYPE_2__ list_args ; 
 int /*<<< orphan*/  list_entries ; 
 TYPE_2__ namespace_args ; 
 TYPE_2__ set_args ; 
 int /*<<< orphan*/  set_namespace ; 
 int /*<<< orphan*/  set_value ; 

void register_nvs(void)
{
    set_args.key = arg_str1(NULL, NULL, "<key>", "key of the value to be set");
    set_args.type = arg_str1(NULL, NULL, "<type>", ARG_TYPE_STR);

    set_args.value = arg_str1("v", "value", "<value>", "value to be stored");
    set_args.end = arg_end(2);

    get_args.key = arg_str1(NULL, NULL, "<key>", "key of the value to be read");
    get_args.type = arg_str1(NULL, NULL, "<type>", ARG_TYPE_STR);
    get_args.end = arg_end(2);

    erase_args.key = arg_str1(NULL, NULL, "<key>", "key of the value to be erased");
    erase_args.end = arg_end(2);

    erase_all_args.namespace = arg_str1(NULL, NULL, "<namespace>", "namespace to be erased");
    erase_all_args.end = arg_end(2);

    namespace_args.namespace = arg_str1(NULL, NULL, "<namespace>", "namespace of the partition to be selected");
    namespace_args.end = arg_end(2);

    list_args.partition = arg_str1(NULL, NULL, "<partition>", "partition name");
    list_args.namespace = arg_str0("n", "namespace", "<namespace>", "namespace name");
    list_args.type = arg_str0("t", "type", "<type>", ARG_TYPE_STR);
    list_args.end = arg_end(2);

    const esp_console_cmd_t set_cmd = {
        .command = "nvs_set",
        .help = "Set key-value pair in selected namespace.\n"
        "Examples:\n"
        " nvs_set VarName i32 -v 123 \n"
        " nvs_set VarName srt -v YourString \n"
        " nvs_set VarName blob -v 0123456789abcdef \n",
        .hint = NULL,
        .func = &set_value,
        .argtable = &set_args
    };

    const esp_console_cmd_t get_cmd = {
        .command = "nvs_get",
        .help = "Get key-value pair from selected namespace. \n"
        "Example: nvs_get VarName i32",
        .hint = NULL,
        .func = &get_value,
        .argtable = &get_args
    };

    const esp_console_cmd_t erase_cmd = {
        .command = "nvs_erase",
        .help = "Erase key-value pair from current namespace",
        .hint = NULL,
        .func = &erase_value,
        .argtable = &erase_args
    };

    const esp_console_cmd_t erase_namespace_cmd = {
        .command = "nvs_erase_namespace",
        .help = "Erases specified namespace",
        .hint = NULL,
        .func = &erase_namespace,
        .argtable = &erase_all_args
    };

    const esp_console_cmd_t namespace_cmd = {
        .command = "nvs_namespace",
        .help = "Set current namespace",
        .hint = NULL,
        .func = &set_namespace,
        .argtable = &namespace_args
    };

    const esp_console_cmd_t list_entries_cmd = {
        .command = "nvs_list",
        .help = "List stored key-value pairs stored in NVS."
        "Namespace and type can be specified to print only those key-value pairs.\n"
        "Following command list variables stored inside 'nvs' partition, under namespace 'storage' with type uint32_t"
        "Example: nvs_list nvs -n storage -t u32 \n",
        .hint = NULL,
        .func = &list_entries,
        .argtable = &list_args
    };

    ESP_ERROR_CHECK(esp_console_cmd_register(&set_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&get_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&erase_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&namespace_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&list_entries_cmd));
    ESP_ERROR_CHECK(esp_console_cmd_register(&erase_namespace_cmd));
}