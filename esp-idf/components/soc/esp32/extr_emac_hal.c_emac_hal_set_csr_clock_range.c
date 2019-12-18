#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* mac_regs; } ;
typedef  TYPE_3__ emac_hal_context_t ;
struct TYPE_5__ {int miicsrclk; } ;
struct TYPE_6__ {TYPE_1__ emacgmiiaddr; } ;

/* Variables and functions */
 int CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ ; 

void emac_hal_set_csr_clock_range(emac_hal_context_t *hal)
{
    /* Tell MAC system clock Frequency, which will determin the frequency range of MDC(1MHz~2.5MHz) */
    if (CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ >= 20 && CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ < 35) {
        hal->mac_regs->emacgmiiaddr.miicsrclk = 2;
    } else if (CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ >= 35 && CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ < 60) {
        hal->mac_regs->emacgmiiaddr.miicsrclk = 3;
    } else if (CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ >= 60 && CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ < 100) {
        hal->mac_regs->emacgmiiaddr.miicsrclk = 0;
    } else if (CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ >= 100 && CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ < 150) {
        hal->mac_regs->emacgmiiaddr.miicsrclk = 1;
    } else if (CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ > 150 && CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ < 250) {
        hal->mac_regs->emacgmiiaddr.miicsrclk = 4;
    } else {
        hal->mac_regs->emacgmiiaddr.miicsrclk = 5;
    }
}