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
struct wb35_reg {int M24_MacControl; } ;
struct hw_data {int CurrentRadioSw; scalar_t__ SurpriseRemove; struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Reg_Write (struct hw_data*,int,int) ; 

__attribute__((used)) static void hal_set_radio_mode(struct hw_data *pHwData, unsigned char radio_off)
{
	struct wb35_reg *reg = &pHwData->reg;

	if (pHwData->SurpriseRemove)
		return;

	if (radio_off)		//disable Baseband receive off
	{
		pHwData->CurrentRadioSw = 1;	// off
		reg->M24_MacControl &= 0xffffffbf;
	} else {
		pHwData->CurrentRadioSw = 0;	// on
		reg->M24_MacControl |= 0x00000040;
	}
	Wb35Reg_Write(pHwData, 0x0824, reg->M24_MacControl);
}