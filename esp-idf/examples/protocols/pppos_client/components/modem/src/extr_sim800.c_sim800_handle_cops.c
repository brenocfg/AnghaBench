#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  oper; } ;
typedef  TYPE_1__ modem_dce_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MODEM_MAX_OPERATOR_LENGTH ; 
 int /*<<< orphan*/  MODEM_RESULT_CODE_ERROR ; 
 int /*<<< orphan*/  MODEM_RESULT_CODE_SUCCESS ; 
 int /*<<< orphan*/  MODEM_STATE_FAIL ; 
 int /*<<< orphan*/  MODEM_STATE_SUCCESS ; 
 int /*<<< orphan*/  esp_modem_process_command_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strip_cr_lf_tail (int /*<<< orphan*/ ,int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 
 scalar_t__ strstr (char const*,int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static esp_err_t sim800_handle_cops(modem_dce_t *dce, const char *line)
{
    esp_err_t err = ESP_FAIL;
    if (strstr(line, MODEM_RESULT_CODE_SUCCESS)) {
        err = esp_modem_process_command_done(dce, MODEM_STATE_SUCCESS);
    } else if (strstr(line, MODEM_RESULT_CODE_ERROR)) {
        err = esp_modem_process_command_done(dce, MODEM_STATE_FAIL);
    } else if (!strncmp(line, "+COPS", strlen("+COPS"))) {
        /* there might be some random spaces in operator's name, we can not use sscanf to parse the result */
        /* strtok will break the string, we need to create a copy */
        size_t len = strlen(line);
        char *line_copy = malloc(len + 1);
        strcpy(line_copy, line);
        /* +COPS: <mode>[, <format>[, <oper>]] */
        char *str_ptr = NULL;
        char *p[3];
        uint8_t i = 0;
        /* strtok will broke string by replacing delimiter with '\0' */
        p[i] = strtok_r(line_copy, ",", &str_ptr);
        while (p[i]) {
            p[++i] = strtok_r(NULL, ",", &str_ptr);
        }
        if (i >= 3) {
            int len = snprintf(dce->oper, MODEM_MAX_OPERATOR_LENGTH, "%s", p[2]);
            if (len > 2) {
                /* Strip "\r\n" */
                strip_cr_lf_tail(dce->oper, len);
                err = ESP_OK;
            }
        }
        free(line_copy);
    }
    return err;
}