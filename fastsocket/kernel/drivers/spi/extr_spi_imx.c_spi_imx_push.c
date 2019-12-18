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
struct spi_imx_data {int txfifo; int /*<<< orphan*/  (* trigger ) (struct spi_imx_data*) ;int /*<<< orphan*/  (* tx ) (struct spi_imx_data*) ;int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct spi_imx_data*) ; 
 int /*<<< orphan*/  stub2 (struct spi_imx_data*) ; 

__attribute__((used)) static void spi_imx_push(struct spi_imx_data *spi_imx)
{
	while (spi_imx->txfifo < 8) {
		if (!spi_imx->count)
			break;
		spi_imx->tx(spi_imx);
		spi_imx->txfifo++;
	}

	spi_imx->trigger(spi_imx);
}