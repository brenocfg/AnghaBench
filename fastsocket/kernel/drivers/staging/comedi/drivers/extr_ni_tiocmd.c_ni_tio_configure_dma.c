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
struct ni_gpct_device {int variant; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int Gi_DMA_Enable_Bit ; 
 unsigned int Gi_DMA_Int_Bit ; 
 unsigned int Gi_DMA_Write_Bit ; 
 unsigned int Gi_Read_Acknowledges_Irq ; 
 unsigned int Gi_Write_Acknowledges_Irq ; 
 int /*<<< orphan*/  NITIO_Gi_DMA_Config_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Input_Select_Reg (int /*<<< orphan*/ ) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void ni_tio_configure_dma(struct ni_gpct *counter, short enable,
				 short read_not_write)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned input_select_bits = 0;

	if (enable) {
		if (read_not_write) {
			input_select_bits |= Gi_Read_Acknowledges_Irq;
		} else {
			input_select_bits |= Gi_Write_Acknowledges_Irq;
		}
	}
	ni_tio_set_bits(counter,
			NITIO_Gi_Input_Select_Reg(counter->counter_index),
			Gi_Read_Acknowledges_Irq | Gi_Write_Acknowledges_Irq,
			input_select_bits);
	switch (counter_dev->variant) {
	case ni_gpct_variant_e_series:
		break;
	case ni_gpct_variant_m_series:
	case ni_gpct_variant_660x:
		{
			unsigned gi_dma_config_bits = 0;

			if (enable) {
				gi_dma_config_bits |= Gi_DMA_Enable_Bit;
				gi_dma_config_bits |= Gi_DMA_Int_Bit;
			}
			if (read_not_write == 0) {
				gi_dma_config_bits |= Gi_DMA_Write_Bit;
			}
			ni_tio_set_bits(counter,
					NITIO_Gi_DMA_Config_Reg(counter->
								counter_index),
					Gi_DMA_Enable_Bit | Gi_DMA_Int_Bit |
					Gi_DMA_Write_Bit, gi_dma_config_bits);
		}
		break;
	}
}