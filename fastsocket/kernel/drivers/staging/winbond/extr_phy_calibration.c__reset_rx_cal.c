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
typedef  int u32 ;
struct hw_data {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_get_dxx_reg (struct hw_data*,int,int*) ; 
 int /*<<< orphan*/  hw_set_dxx_reg (struct hw_data*,int,int) ; 

void _reset_rx_cal(struct hw_data *phw_data)
{
	u32     val;

	hw_get_dxx_reg(phw_data, 0x54, &val);

	if (phw_data->revision == 0x2002) // 1st-cut
	{
		val &= 0xFFFF0000;
	}
	else // 2nd-cut
	{
		val &= 0x000003FF;
	}

	hw_set_dxx_reg(phw_data, 0x54, val);
}