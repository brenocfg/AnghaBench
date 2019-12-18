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
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int (* func ) (size_t,char**) ;} ;
typedef  TYPE_1__ cmd_item_t ;
struct TYPE_5__ {int /*<<< orphan*/  max_cmdline_args; int /*<<< orphan*/  max_cmdline_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 size_t esp_console_split_argv (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_command_by_name (char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 TYPE_2__ s_config ; 
 int /*<<< orphan*/ * s_tmp_line_buf ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int stub1 (size_t,char**) ; 

esp_err_t esp_console_run(const char *cmdline, int *cmd_ret)
{
    if (s_tmp_line_buf == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    char **argv = (char **) calloc(s_config.max_cmdline_args, sizeof(char *));
    if (argv == NULL) {
        return ESP_ERR_NO_MEM;
    }
    strlcpy(s_tmp_line_buf, cmdline, s_config.max_cmdline_length);

    size_t argc = esp_console_split_argv(s_tmp_line_buf, argv,
                                         s_config.max_cmdline_args);
    if (argc == 0) {
        free(argv);
        return ESP_ERR_INVALID_ARG;
    }
    const cmd_item_t *cmd = find_command_by_name(argv[0]);
    if (cmd == NULL) {
        free(argv);
        return ESP_ERR_NOT_FOUND;
    }
    *cmd_ret = (*cmd->func)(argc, argv);
    free(argv);
    return ESP_OK;
}