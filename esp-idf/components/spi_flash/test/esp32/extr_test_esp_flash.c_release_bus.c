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
 int HSPI_HOST ; 
 int VSPI_HOST ; 
 int /*<<< orphan*/  spi_bus_free (int) ; 

__attribute__((used)) static void release_bus(int host_id)
{
    if (host_id == HSPI_HOST || host_id == VSPI_HOST) {
        spi_bus_free(host_id);
    }
}