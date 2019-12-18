#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ret; void* arg; } ;
typedef  TYPE_1__ wps_ioctl_param_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  s_wps_api_sem ; 
 scalar_t__ wps_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wps_post_block(uint32_t sig, void *arg)
{
    wps_ioctl_param_t param;

    param.ret = ESP_FAIL;
    param.arg = arg;

    if (ESP_OK != wps_post(sig, (uint32_t)&param)) {
        return ESP_FAIL;
    }

    if (pdPASS == xSemaphoreTake(s_wps_api_sem, portMAX_DELAY)) {
        return param.ret;
    } else {
        return ESP_FAIL;
    }
}