#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intelfb_info {int num_outputs; int chipset; TYPE_1__* output; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_bus; void* type; int /*<<< orphan*/  ddc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOD ; 
 int /*<<< orphan*/  GPIOE ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 void* INTELFB_OUTPUT_ANALOG ; 
 void* INTELFB_OUTPUT_DVO ; 
 void* INTELFB_OUTPUT_SDVO ; 
#define  INTEL_830M 139 
#define  INTEL_845G 138 
#define  INTEL_854 137 
#define  INTEL_855GM 136 
#define  INTEL_865G 135 
#define  INTEL_915G 134 
#define  INTEL_915GM 133 
#define  INTEL_945G 132 
#define  INTEL_945GM 131 
#define  INTEL_945GME 130 
#define  INTEL_965G 129 
#define  INTEL_965GM 128 
 int /*<<< orphan*/  intelfb_setup_i2c_bus (struct intelfb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void intelfb_create_i2c_busses(struct intelfb_info *dinfo)
{
	int i = 0;

	/* everyone has at least a single analog output */
	dinfo->num_outputs = 1;
	dinfo->output[i].type = INTELFB_OUTPUT_ANALOG;

	/* setup the DDC bus for analog output */
	intelfb_setup_i2c_bus(dinfo, &dinfo->output[i].ddc_bus, GPIOA,
			      "CRTDDC_A", I2C_CLASS_DDC);
	i++;

	/* need to add the output busses for each device
	   - this function is very incomplete
	   - i915GM has LVDS and TVOUT for example
	*/
	switch(dinfo->chipset) {
	case INTEL_830M:
	case INTEL_845G:
	case INTEL_854:
	case INTEL_855GM:
	case INTEL_865G:
		dinfo->output[i].type = INTELFB_OUTPUT_DVO;
		intelfb_setup_i2c_bus(dinfo, &dinfo->output[i].ddc_bus,
				      GPIOD, "DVODDC_D", I2C_CLASS_DDC);
		intelfb_setup_i2c_bus(dinfo, &dinfo->output[i].i2c_bus,
				      GPIOE, "DVOI2C_E", 0);
		i++;
		break;
	case INTEL_915G:
	case INTEL_915GM:
		/* has some LVDS + tv-out */
	case INTEL_945G:
	case INTEL_945GM:
	case INTEL_945GME:
	case INTEL_965G:
	case INTEL_965GM:
		/* SDVO ports have a single control bus - 2 devices */
		dinfo->output[i].type = INTELFB_OUTPUT_SDVO;
		intelfb_setup_i2c_bus(dinfo, &dinfo->output[i].i2c_bus,
				      GPIOE, "SDVOCTRL_E", 0);
		/* TODO: initialize the SDVO */
		/* I830SDVOInit(pScrn, i, DVOB); */
		i++;

		/* set up SDVOC */
		dinfo->output[i].type = INTELFB_OUTPUT_SDVO;
		dinfo->output[i].i2c_bus = dinfo->output[i - 1].i2c_bus;
		/* TODO: initialize the SDVO */
		/* I830SDVOInit(pScrn, i, DVOC); */
		i++;
		break;
	}
	dinfo->num_outputs = i;
}