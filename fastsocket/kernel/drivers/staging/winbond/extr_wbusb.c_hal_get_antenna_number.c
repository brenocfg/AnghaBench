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
struct wb35_reg {int BB2C; } ;
struct hw_data {struct wb35_reg reg; } ;

/* Variables and functions */
 int BIT (int) ; 

u8 hal_get_antenna_number(struct hw_data *pHwData)
{
	struct wb35_reg *reg = &pHwData->reg;

	if ((reg->BB2C & BIT(11)) == 0)
		return 0;
	else
		return 1;
}