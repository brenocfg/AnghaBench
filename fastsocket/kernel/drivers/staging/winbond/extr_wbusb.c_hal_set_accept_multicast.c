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
typedef  scalar_t__ u8 ;
struct wb35_reg {int M00_MacControl; } ;
struct hw_data {scalar_t__ SurpriseRemove; struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Reg_Write (struct hw_data*,int,int) ; 

__attribute__((used)) static void hal_set_accept_multicast(struct hw_data *pHwData, u8 enable)
{
	struct wb35_reg *reg = &pHwData->reg;

	if (pHwData->SurpriseRemove)
		return;

	reg->M00_MacControl &= ~0x01000000;	//The HW value
	if (enable)
		reg->M00_MacControl |= 0x01000000;	//The HW value
	Wb35Reg_Write(pHwData, 0x0800, reg->M00_MacControl);
}