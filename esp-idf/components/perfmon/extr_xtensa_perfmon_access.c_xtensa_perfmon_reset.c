#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int ERI_PERFMON_MAX ; 
 scalar_t__ ERI_PERFMON_PM0 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  eri_write (scalar_t__,int /*<<< orphan*/ ) ; 

esp_err_t xtensa_perfmon_reset(int id)
{
    if (id >= ERI_PERFMON_MAX) {
        return ESP_ERR_INVALID_ARG;
    }
    eri_write(ERI_PERFMON_PM0 + id * sizeof(int32_t), 0);
    return ESP_OK;
}