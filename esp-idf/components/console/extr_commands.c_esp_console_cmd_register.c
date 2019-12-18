#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_11__ {int /*<<< orphan*/  func; scalar_t__ argtable; int /*<<< orphan*/  hint; int /*<<< orphan*/  help; int /*<<< orphan*/ * command; } ;
typedef  TYPE_1__ esp_console_cmd_t ;
struct TYPE_12__ {char* hint; int /*<<< orphan*/  func; scalar_t__ argtable; int /*<<< orphan*/  help; int /*<<< orphan*/ * command; } ;
typedef  TYPE_2__ cmd_item_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* SLIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_print_syntax (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * open_memstream (char**,size_t*) ; 
 int /*<<< orphan*/  s_cmd_list ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ *,char) ; 

esp_err_t esp_console_cmd_register(const esp_console_cmd_t *cmd)
{
    cmd_item_t *item = (cmd_item_t *) calloc(1, sizeof(*item));
    if (item == NULL) {
        return ESP_ERR_NO_MEM;
    }
    if (cmd->command == NULL) {
        free(item);
        return ESP_ERR_INVALID_ARG;
    }
    if (strchr(cmd->command, ' ') != NULL) {
        free(item);
        return ESP_ERR_INVALID_ARG;
    }
    item->command = cmd->command;
    item->help = cmd->help;
    if (cmd->hint) {
        /* Prepend a space before the hint. It separates command name and
         * the hint. arg_print_syntax below adds this space as well.
         */
        int unused __attribute__((unused));
        unused = asprintf(&item->hint, " %s", cmd->hint);
    } else if (cmd->argtable) {
        /* Generate hint based on cmd->argtable */
        char *buf = NULL;
        size_t buf_size = 0;
        FILE *f = open_memstream(&buf, &buf_size);
        if (f != NULL) {
            arg_print_syntax(f, cmd->argtable, NULL);
            fclose(f);
        }
        item->hint = buf;
    }
    item->argtable = cmd->argtable;
    item->func = cmd->func;
    cmd_item_t *last = SLIST_FIRST(&s_cmd_list);
    if (last == NULL) {
        SLIST_INSERT_HEAD(&s_cmd_list, item, next);
    } else {
        cmd_item_t *it;
        while ((it = SLIST_NEXT(last, next)) != NULL) {
            last = it;
        }
        SLIST_INSERT_AFTER(last, item, next);
    }
    return ESP_OK;
}