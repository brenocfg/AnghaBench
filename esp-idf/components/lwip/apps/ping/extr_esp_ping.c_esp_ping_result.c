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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  esp_ping_found ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {scalar_t__ min_time; scalar_t__ max_time; int /*<<< orphan*/  recv_count; int /*<<< orphan*/  total_time; int /*<<< orphan*/  timeout_count; int /*<<< orphan*/  send_count; int /*<<< orphan*/  total_bytes; scalar_t__ resp_time; scalar_t__ bytes; scalar_t__ ping_err; } ;
struct TYPE_5__ {TYPE_1__ ping_res; int /*<<< orphan*/  (* ping_res_fn ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ PING_RES_FINISH ; 
 scalar_t__ PING_RES_TIMEOUT ; 
 int /*<<< orphan*/  PING_TARGET_RES_FN ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ping_option_info ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

esp_err_t esp_ping_result(uint8_t res_val, uint16_t ping_len, uint32_t ping_time)
{
    esp_err_t ret = ESP_OK;

    ping_option_info->ping_res.ping_err = res_val;

    if (res_val != PING_RES_FINISH) {
        ping_option_info->ping_res.bytes = ping_len;
        ping_option_info->ping_res.resp_time = ping_time;
        ping_option_info->ping_res.total_bytes += ping_len;
        ping_option_info->ping_res.send_count ++;

        if (res_val == PING_RES_TIMEOUT) {
            ping_option_info->ping_res.timeout_count ++;
        } else {
            if (!ping_option_info->ping_res.min_time || (ping_time < ping_option_info->ping_res.min_time)) {
                ping_option_info->ping_res.min_time = ping_time;
            }

            if (ping_time > ping_option_info->ping_res.max_time) {
                ping_option_info->ping_res.max_time = ping_time;
            }


            ping_option_info->ping_res.total_time += ping_time;
            ping_option_info->ping_res.recv_count ++;
        }
    }

    if (ping_option_info->ping_res_fn) {
        ping_option_info->ping_res_fn(PING_TARGET_RES_FN, &ping_option_info->ping_res);
        if (res_val == PING_RES_FINISH) {
            memset(&ping_option_info->ping_res, 0, sizeof(esp_ping_found));
        }
    }

    return ret;
}