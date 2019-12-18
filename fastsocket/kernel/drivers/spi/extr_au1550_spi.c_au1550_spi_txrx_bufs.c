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
struct spi_transfer {int dummy; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct au1550_spi {int (* txrx_bufs ) (struct spi_device*,struct spi_transfer*) ;} ;

/* Variables and functions */
 struct au1550_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int stub1 (struct spi_device*,struct spi_transfer*) ; 

__attribute__((used)) static int au1550_spi_txrx_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct au1550_spi *hw = spi_master_get_devdata(spi->master);
	return hw->txrx_bufs(spi, t);
}