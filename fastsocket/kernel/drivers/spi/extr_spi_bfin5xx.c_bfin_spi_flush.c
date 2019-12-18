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
struct driver_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_STAT_CLR ; 
 int BIT_STAT_SPIF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int loops_per_jiffy ; 
 int read_STAT (struct driver_data*) ; 
 int /*<<< orphan*/  write_STAT (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfin_spi_flush(struct driver_data *drv_data)
{
	unsigned long limit = loops_per_jiffy << 1;

	/* wait for stop and clear stat */
	while (!(read_STAT(drv_data) & BIT_STAT_SPIF) && --limit)
		cpu_relax();

	write_STAT(drv_data, BIT_STAT_CLR);

	return limit;
}