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
struct spi_imx_data {scalar_t__ base; } ;

/* Variables and functions */
 int MX27_INTREG_RR ; 
 scalar_t__ MXC_CSPIINT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int mx27_rx_available(struct spi_imx_data *spi_imx)
{
	return readl(spi_imx->base + MXC_CSPIINT) & MX27_INTREG_RR;
}