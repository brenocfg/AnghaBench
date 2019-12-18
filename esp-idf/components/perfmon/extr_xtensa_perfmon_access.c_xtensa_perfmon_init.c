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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int ERI_PERFMON_MAX ; 
 scalar_t__ ERI_PERFMON_PM0 ; 
 scalar_t__ ERI_PERFMON_PMCTRL0 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int PMCTRL_KRNLCNT_SHIFT ; 
 int PMCTRL_MASK_MASK ; 
 int PMCTRL_MASK_SHIFT ; 
 int PMCTRL_SELECT_MASK ; 
 int PMCTRL_SELECT_SHIFT ; 
 int PMCTRL_TRACELEVEL_MASK ; 
 int PMCTRL_TRACELEVEL_SHIFT ; 
 int /*<<< orphan*/  eri_write (scalar_t__,int) ; 

esp_err_t xtensa_perfmon_init(int id, uint16_t select, uint16_t mask, int kernelcnt, int tracelevel)
{
    if (id >= ERI_PERFMON_MAX) {
        return ESP_ERR_INVALID_ARG;
    }
    uint32_t pmc =
        ((tracelevel & PMCTRL_TRACELEVEL_MASK) << PMCTRL_TRACELEVEL_SHIFT) |
        ((select & PMCTRL_SELECT_MASK) << PMCTRL_SELECT_SHIFT) |
        ((mask & PMCTRL_MASK_MASK) << PMCTRL_MASK_SHIFT) |
        ((kernelcnt & 1) << PMCTRL_KRNLCNT_SHIFT);

    eri_write(ERI_PERFMON_PM0 + id * sizeof(int32_t), 0);
    eri_write(ERI_PERFMON_PMCTRL0 + id * sizeof(int32_t), pmc);
    return ESP_OK;
}