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
typedef  size_t spi_host_device_t ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGE (int /*<<< orphan*/ ,char*,size_t,char const*) ; 
 int /*<<< orphan*/  SPI_TAG ; 
 int atomic_compare_exchange_strong (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 char const** spi_claiming_func ; 
 int /*<<< orphan*/ * spi_periph_claimed ; 
 TYPE_1__* spi_periph_signal ; 

bool spicommon_periph_claim(spi_host_device_t host, const char* source)
{
    bool false_var = false;
    bool ret = atomic_compare_exchange_strong(&spi_periph_claimed[host], &false_var, true);
    if (ret) {
        spi_claiming_func[host] = source;
        periph_module_enable(spi_periph_signal[host].module);
    } else {
        ESP_EARLY_LOGE(SPI_TAG, "SPI%d already claimed by %s.", host+1, spi_claiming_func[host]);
    }
    return ret;
}