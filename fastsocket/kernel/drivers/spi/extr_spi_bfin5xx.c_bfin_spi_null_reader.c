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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct driver_data {scalar_t__ n_bytes; scalar_t__ rx; scalar_t__ rx_end; TYPE_1__* cur_chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  idle_tx_val; } ;

/* Variables and functions */
 int BIT_STAT_RXS ; 
 int /*<<< orphan*/  bfin_spi_dummy_read (struct driver_data*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int read_STAT (struct driver_data*) ; 
 int /*<<< orphan*/  write_TDBR (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_spi_null_reader(struct driver_data *drv_data)
{
	u8 n_bytes = drv_data->n_bytes;
	u16 tx_val = drv_data->cur_chip->idle_tx_val;

	/* discard old RX data and clear RXS */
	bfin_spi_dummy_read(drv_data);

	while (drv_data->rx < drv_data->rx_end) {
		write_TDBR(drv_data, tx_val);
		drv_data->rx += n_bytes;
		while (!(read_STAT(drv_data) & BIT_STAT_RXS))
			cpu_relax();
		bfin_spi_dummy_read(drv_data);
	}
}