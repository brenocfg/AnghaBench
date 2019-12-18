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
 int spi_hal_get_freq_limit (int,int) ; 

int spi_get_freq_limit(bool gpio_is_used, int input_delay_ns)
{
    return spi_hal_get_freq_limit(gpio_is_used, input_delay_ns);

}