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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct hw_data {int dummy; } ;

/* Variables and functions */
 unsigned char Wb35Reg_ReadSync (struct hw_data*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned char hal_get_dxx_reg(struct hw_data *pHwData, u16 number, u32 * pValue)
{
	if (number < 0x1000)
		number += 0x1000;
	return Wb35Reg_ReadSync(pHwData, number, pValue);
}