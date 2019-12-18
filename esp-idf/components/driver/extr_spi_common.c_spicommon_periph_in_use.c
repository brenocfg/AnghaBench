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
typedef  size_t spi_host_device_t ;

/* Variables and functions */
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spi_periph_claimed ; 

bool spicommon_periph_in_use(spi_host_device_t host)
{
    return atomic_load(&spi_periph_claimed[host]);
}