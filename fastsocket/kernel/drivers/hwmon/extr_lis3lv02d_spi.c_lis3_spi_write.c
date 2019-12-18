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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tmp ;
struct spi_device {int dummy; } ;
struct lis3lv02d {struct spi_device* bus_priv; } ;

/* Variables and functions */
 int spi_write (struct spi_device*,int*,int) ; 

__attribute__((used)) static int lis3_spi_write(struct lis3lv02d *lis3, int reg, u8 val)
{
	u8 tmp[2] = { reg, val };
	struct spi_device *spi = lis3->bus_priv;
	return spi_write(spi, tmp, sizeof(tmp));
}