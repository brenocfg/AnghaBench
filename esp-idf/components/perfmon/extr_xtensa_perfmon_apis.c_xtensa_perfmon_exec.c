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
struct TYPE_3__ {size_t counters_size; size_t repeat_count; int* select_mask; scalar_t__ max_deviation; int /*<<< orphan*/  callback_params; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int,int,scalar_t__) ;int /*<<< orphan*/  call_params; int /*<<< orphan*/  (* call_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  tracelevel; } ;
typedef  TYPE_1__ xtensa_perfmon_config_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  xtensa_perfmon_init (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtensa_perfmon_start () ; 
 int /*<<< orphan*/  xtensa_perfmon_stop () ; 
 scalar_t__ xtensa_perfmon_value (int) ; 

esp_err_t xtensa_perfmon_exec(const xtensa_perfmon_config_t *config)
{
    esp_err_t result = ESP_OK;
    if (config->call_function == NULL) {
        ESP_LOGE(TAG, "Parameter call_function must be defined.");
        return ESP_ERR_INVALID_ARG;
    }
    if (config->callback == NULL) {
        ESP_LOGE(TAG, "Parameter callback must be defined.");
        return ESP_ERR_INVALID_ARG;
    }
    for (size_t n = 0; n < config->counters_size; n++) {
        uint32_t call_min = UINT32_MAX;
        uint32_t call_max = 0;
        float result_value = 0;

        for (size_t i = 0; i < config->repeat_count; i++) {
            // Set up cycle counter
            xtensa_perfmon_stop();
            int kernelcnt = 0;
            // if tracelevel used, then kernelcnt will be enabled
            if (config->tracelevel >=0) kernelcnt = 1;
            xtensa_perfmon_init(0, 0, 0xffff, kernelcnt, config->tracelevel);
            xtensa_perfmon_init(1, config->select_mask[n * 2 + 0], config->select_mask[n * 2 + 1], kernelcnt, config->tracelevel);
            xtensa_perfmon_start();
            config->call_function(config->call_params);
            xtensa_perfmon_stop();
            uint32_t p0 = xtensa_perfmon_value(0);
            uint32_t p1 = xtensa_perfmon_value(1);
            result_value += (float)p1 / config->repeat_count;
            if (p0 < call_min) {
                call_min = p0;
            }
            if (p0 > call_max) {
                call_max = p0;
            }
            ESP_LOGV(TAG, "p0 = %i, p1 = %i", p0, p1);
        }
        uint32_t call_diff = (call_max - call_min);

        if (call_diff > call_max * config->max_deviation) {
            return ESP_FAIL;
        } else {
            config->callback(config->callback_params, config->select_mask[n * 2 + 0], config->select_mask[n * 2 + 1], (uint32_t)result_value);
        }
    }
    return result;
}