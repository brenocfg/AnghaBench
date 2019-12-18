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
struct spi_imx_data {scalar_t__ base; int /*<<< orphan*/  spi_clk; } ;
struct spi_imx_config {int bpw; int mode; int cs; int /*<<< orphan*/  speed_hz; } ;

/* Variables and functions */
 int MX27_CSPICTRL_CS_SHIFT ; 
 unsigned int MX27_CSPICTRL_DR_SHIFT ; 
 unsigned int MX27_CSPICTRL_ENABLE ; 
 unsigned int MX27_CSPICTRL_MASTER ; 
 unsigned int MX27_CSPICTRL_PHA ; 
 unsigned int MX27_CSPICTRL_POL ; 
 unsigned int MX27_CSPICTRL_SSPOL ; 
 scalar_t__ MXC_CSPICTRL ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_CS_HIGH ; 
 unsigned int spi_imx_clkdiv_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mx27_config(struct spi_imx_data *spi_imx,
		struct spi_imx_config *config)
{
	unsigned int reg = MX27_CSPICTRL_ENABLE | MX27_CSPICTRL_MASTER;

	reg |= spi_imx_clkdiv_1(spi_imx->spi_clk, config->speed_hz) <<
		MX27_CSPICTRL_DR_SHIFT;
	reg |= config->bpw - 1;

	if (config->mode & SPI_CPHA)
		reg |= MX27_CSPICTRL_PHA;
	if (config->mode & SPI_CPOL)
		reg |= MX27_CSPICTRL_POL;
	if (config->mode & SPI_CS_HIGH)
		reg |= MX27_CSPICTRL_SSPOL;
	if (config->cs < 0)
		reg |= (config->cs + 32) << MX27_CSPICTRL_CS_SHIFT;

	writel(reg, spi_imx->base + MXC_CSPICTRL);

	return 0;
}