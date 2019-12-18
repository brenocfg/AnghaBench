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
struct spi_transfer {int bits_per_word; scalar_t__ speed_hz; } ;
struct spi_imx_data {int /*<<< orphan*/  (* config ) (struct spi_imx_data*,struct spi_imx_config*) ;int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/ * chipselect; } ;
struct spi_imx_config {int bpw; scalar_t__ speed_hz; int /*<<< orphan*/  cs; int /*<<< orphan*/  mode; } ;
struct spi_device {int bits_per_word; size_t chip_select; scalar_t__ max_speed_hz; int /*<<< orphan*/  mode; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u16 ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u32 ; 
 int /*<<< orphan*/  spi_imx_buf_rx_u8 ; 
 int /*<<< orphan*/  spi_imx_buf_tx_u16 ; 
 int /*<<< orphan*/  spi_imx_buf_tx_u32 ; 
 int /*<<< orphan*/  spi_imx_buf_tx_u8 ; 
 struct spi_imx_data* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct spi_imx_data*,struct spi_imx_config*) ; 

__attribute__((used)) static int spi_imx_setupxfer(struct spi_device *spi,
				 struct spi_transfer *t)
{
	struct spi_imx_data *spi_imx = spi_master_get_devdata(spi->master);
	struct spi_imx_config config;

	config.bpw = t ? t->bits_per_word : spi->bits_per_word;
	config.speed_hz  = t ? t->speed_hz : spi->max_speed_hz;
	config.mode = spi->mode;
	config.cs = spi_imx->chipselect[spi->chip_select];

	if (!config.speed_hz)
		config.speed_hz = spi->max_speed_hz;
	if (!config.bpw)
		config.bpw = spi->bits_per_word;
	if (!config.speed_hz)
		config.speed_hz = spi->max_speed_hz;

	/* Initialize the functions for transfer */
	if (config.bpw <= 8) {
		spi_imx->rx = spi_imx_buf_rx_u8;
		spi_imx->tx = spi_imx_buf_tx_u8;
	} else if (config.bpw <= 16) {
		spi_imx->rx = spi_imx_buf_rx_u16;
		spi_imx->tx = spi_imx_buf_tx_u16;
	} else if (config.bpw <= 32) {
		spi_imx->rx = spi_imx_buf_rx_u32;
		spi_imx->tx = spi_imx_buf_tx_u32;
	} else
		BUG();

	spi_imx->config(spi_imx, &config);

	return 0;
}