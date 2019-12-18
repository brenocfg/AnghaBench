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
typedef  scalar_t__ trax_ena_select_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_APP_TRACEMEM_ENA_REG ; 
 int /*<<< orphan*/  DPORT_PRO_TRACEMEM_ENA_REG ; 
 int /*<<< orphan*/  DPORT_TRACEMEM_MUX_MODE_REG ; 
 int /*<<< orphan*/  DPORT_WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int TRACEMEM_MUX_BLK0_ONLY ; 
 int TRACEMEM_MUX_PROBLK0_APPBLK1 ; 
 int TRACEMEM_MUX_PROBLK1_APPBLK0 ; 
 scalar_t__ TRAX_ENA_APP ; 
 scalar_t__ TRAX_ENA_PRO ; 
 scalar_t__ TRAX_ENA_PRO_APP ; 
 scalar_t__ TRAX_ENA_PRO_APP_SWAP ; 

int trax_enable(trax_ena_select_t which) 
{
#if !CONFIG_ESP32_TRAX
    ESP_LOGE(TAG, "Trax_enable called, but trax is disabled in menuconfig!");
    return ESP_ERR_NO_MEM;
#endif
#if !CONFIG_ESP32_TRAX_TWOBANKS
    if (which == TRAX_ENA_PRO_APP || which == TRAX_ENA_PRO_APP_SWAP) return ESP_ERR_NO_MEM;
#endif
    if (which == TRAX_ENA_PRO_APP || which == TRAX_ENA_PRO_APP_SWAP) {
        DPORT_WRITE_PERI_REG(DPORT_TRACEMEM_MUX_MODE_REG, (which == TRAX_ENA_PRO_APP_SWAP)?TRACEMEM_MUX_PROBLK1_APPBLK0:TRACEMEM_MUX_PROBLK0_APPBLK1);
    } else {
        DPORT_WRITE_PERI_REG(DPORT_TRACEMEM_MUX_MODE_REG, TRACEMEM_MUX_BLK0_ONLY);
    }
    DPORT_WRITE_PERI_REG(DPORT_PRO_TRACEMEM_ENA_REG, (which == TRAX_ENA_PRO_APP || which == TRAX_ENA_PRO_APP_SWAP || which == TRAX_ENA_PRO));
    DPORT_WRITE_PERI_REG(DPORT_APP_TRACEMEM_ENA_REG, (which == TRAX_ENA_PRO_APP || which == TRAX_ENA_PRO_APP_SWAP || which == TRAX_ENA_APP));
    return ESP_OK;
}