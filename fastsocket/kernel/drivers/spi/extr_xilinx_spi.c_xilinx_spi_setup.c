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
struct spi_bitbang {int dummy; } ;
struct xilinx_spi {struct spi_bitbang bitbang; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 struct xilinx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int xilinx_spi_setup_transfer (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xilinx_spi_setup(struct spi_device *spi)
{
	struct spi_bitbang *bitbang;
	struct xilinx_spi *xspi;
	int retval;

	xspi = spi_master_get_devdata(spi->master);
	bitbang = &xspi->bitbang;

	retval = xilinx_spi_setup_transfer(spi, NULL);
	if (retval < 0)
		return retval;

	return 0;
}