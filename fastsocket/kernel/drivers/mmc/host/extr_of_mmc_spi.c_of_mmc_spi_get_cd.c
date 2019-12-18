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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_GPIO ; 
 int of_mmc_spi_read_gpio (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_mmc_spi_get_cd(struct device *dev)
{
	return of_mmc_spi_read_gpio(dev, CD_GPIO);
}