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

/* Variables and functions */
 int /*<<< orphan*/  ERI_TRAX_DELAYCNT ; 
 int /*<<< orphan*/  ERI_TRAX_TRAXCTRL ; 
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int TRAXCTRL_TRSTP ; 
 int eri_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eri_write (int /*<<< orphan*/ ,int) ; 

int trax_trigger_traceend_after_delay(int delay) 
{
#if !CONFIG_ESP32_TRAX
    ESP_LOGE(TAG, "Trax_trigger_traceend_after_delay called, but trax is disabled in menuconfig!");
    return ESP_ERR_NO_MEM;
#endif
    eri_write(ERI_TRAX_DELAYCNT, delay);
    eri_write(ERI_TRAX_TRAXCTRL, eri_read(ERI_TRAX_TRAXCTRL)|TRAXCTRL_TRSTP);
    return ESP_OK;
}