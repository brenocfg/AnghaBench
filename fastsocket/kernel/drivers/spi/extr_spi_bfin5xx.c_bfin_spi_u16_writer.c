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
struct driver_data {scalar_t__ tx; scalar_t__ tx_end; } ;

/* Variables and functions */
 int BIT_STAT_RXS ; 
 int /*<<< orphan*/  bfin_spi_dummy_read (struct driver_data*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int read_STAT (struct driver_data*) ; 
 int /*<<< orphan*/  write_TDBR (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_spi_u16_writer(struct driver_data *drv_data)
{
	/* clear RXS (we check for RXS inside the loop) */
	bfin_spi_dummy_read(drv_data);

	while (drv_data->tx < drv_data->tx_end) {
		write_TDBR(drv_data, (*(u16 *) (drv_data->tx)));
		drv_data->tx += 2;
		/* wait until transfer finished.
		   checking SPIF or TXS may not guarantee transfer completion */
		while (!(read_STAT(drv_data) & BIT_STAT_RXS))
			cpu_relax();
		/* discard RX data and clear RXS */
		bfin_spi_dummy_read(drv_data);
	}
}