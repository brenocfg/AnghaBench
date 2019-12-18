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
struct efx_spi_device {size_t block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALCON_SPI_MAX_LEN ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static size_t
falcon_spi_write_limit(const struct efx_spi_device *spi, size_t start)
{
	return min(FALCON_SPI_MAX_LEN,
		   (spi->block_size - (start & (spi->block_size - 1))));
}