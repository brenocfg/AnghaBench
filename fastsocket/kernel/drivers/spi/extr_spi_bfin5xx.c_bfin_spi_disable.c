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
typedef  int u16 ;
struct driver_data {int dummy; } ;

/* Variables and functions */
 int BIT_CTL_ENABLE ; 
 int read_CTRL (struct driver_data*) ; 
 int /*<<< orphan*/  write_CTRL (struct driver_data*,int) ; 

__attribute__((used)) static void bfin_spi_disable(struct driver_data *drv_data)
{
	u16 cr;

	cr = read_CTRL(drv_data);
	write_CTRL(drv_data, (cr & (~BIT_CTL_ENABLE)));
}