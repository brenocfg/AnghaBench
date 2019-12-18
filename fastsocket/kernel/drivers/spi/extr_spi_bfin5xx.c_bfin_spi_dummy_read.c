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
 int /*<<< orphan*/  read_RDBR (struct driver_data*) ; 

__attribute__((used)) static inline void bfin_spi_dummy_read(struct driver_data *drv_data)
{
	(void) read_RDBR(drv_data);
}