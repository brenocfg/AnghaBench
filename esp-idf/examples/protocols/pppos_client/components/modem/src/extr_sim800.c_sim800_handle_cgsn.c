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
struct TYPE_4__ {int /*<<< orphan*/  imei; } ;
typedef  TYPE_1__ modem_dce_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MODEM_IMEI_LENGTH ; 
 int /*<<< orphan*/  MODEM_RESULT_CODE_ERROR ; 
 int /*<<< orphan*/  MODEM_RESULT_CODE_SUCCESS ; 
 int /*<<< orphan*/  MODEM_STATE_FAIL ; 
 int /*<<< orphan*/  MODEM_STATE_SUCCESS ; 
 int /*<<< orphan*/  esp_modem_process_command_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  strip_cr_lf_tail (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t sim800_handle_cgsn(modem_dce_t *dce, const char *line)
{
    esp_err_t err = ESP_FAIL;
    if (strstr(line, MODEM_RESULT_CODE_SUCCESS)) {
        err = esp_modem_process_command_done(dce, MODEM_STATE_SUCCESS);
    } else if (strstr(line, MODEM_RESULT_CODE_ERROR)) {
        err = esp_modem_process_command_done(dce, MODEM_STATE_FAIL);
    } else {
        int len = snprintf(dce->imei, MODEM_IMEI_LENGTH + 1, "%s", line);
        if (len > 2) {
            /* Strip "\r\n" */
            strip_cr_lf_tail(dce->imei, len);
            err = ESP_OK;
        }
    }
    return err;
}