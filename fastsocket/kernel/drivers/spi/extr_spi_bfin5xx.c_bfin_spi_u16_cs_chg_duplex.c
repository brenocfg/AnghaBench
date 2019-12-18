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
typedef  int /*<<< orphan*/  u16 ;
struct driver_data {scalar_t__ rx; scalar_t__ rx_end; scalar_t__ tx; struct chip_data* cur_chip; } ;
struct chip_data {int dummy; } ;

/* Variables and functions */
 int BIT_STAT_RXS ; 
 int /*<<< orphan*/  bfin_spi_cs_active (struct driver_data*,struct chip_data*) ; 
 int /*<<< orphan*/  bfin_spi_cs_deactive (struct driver_data*,struct chip_data*) ; 
 int /*<<< orphan*/  bfin_spi_dummy_read (struct driver_data*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  read_RDBR (struct driver_data*) ; 
 int read_STAT (struct driver_data*) ; 
 int /*<<< orphan*/  write_TDBR (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_spi_u16_cs_chg_duplex(struct driver_data *drv_data)
{
	struct chip_data *chip = drv_data->cur_chip;

	/* discard old RX data and clear RXS */
	bfin_spi_dummy_read(drv_data);

	while (drv_data->rx < drv_data->rx_end) {
		bfin_spi_cs_active(drv_data, chip);
		write_TDBR(drv_data, (*(u16 *) (drv_data->tx)));
		drv_data->tx += 2;
		while (!(read_STAT(drv_data) & BIT_STAT_RXS))
			cpu_relax();
		*(u16 *) (drv_data->rx) = read_RDBR(drv_data);
		drv_data->rx += 2;
		bfin_spi_cs_deactive(drv_data, chip);
	}
}