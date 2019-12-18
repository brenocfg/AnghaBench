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
typedef  int u16 ;
struct iwl_priv {TYPE_1__* nvm_data; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  kelvin_voltage; int /*<<< orphan*/  kelvin_temperature; } ;

/* Variables and functions */
 int IWL_5150_VOLTAGE_TO_TEMPERATURE_COEFF ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 iwl_temp_calib_to_offset(struct iwl_priv *priv)
{
	u16 temperature, voltage;

	temperature = le16_to_cpu(priv->nvm_data->kelvin_temperature);
	voltage = le16_to_cpu(priv->nvm_data->kelvin_voltage);

	/* offset = temp - volt / coeff */
	return (s32)(temperature -
			voltage / IWL_5150_VOLTAGE_TO_TEMPERATURE_COEFF);
}