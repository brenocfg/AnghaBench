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
struct ltc4245_data {int* vregs; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  LTC4245_12VSENSE 131 
#define  LTC4245_3VSENSE 130 
#define  LTC4245_5VSENSE 129 
#define  LTC4245_VEESENSE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct ltc4245_data* ltc4245_update_device (struct device*) ; 

__attribute__((used)) static unsigned int ltc4245_get_current(struct device *dev, u8 reg)
{
	struct ltc4245_data *data = ltc4245_update_device(dev);
	const u8 regval = data->vregs[reg - 0x10];
	unsigned int voltage;
	unsigned int curr;

	/* The strange looking conversions that follow are fixed-point
	 * math, since we cannot do floating point in the kernel.
	 *
	 * Step 1: convert sense register to microVolts
	 * Step 2: convert voltage to milliAmperes
	 *
	 * If you play around with the V=IR equation, you come up with
	 * the following: X uV / Y mOhm == Z mA
	 *
	 * With the resistors that are fractions of a milliOhm, we multiply
	 * the voltage and resistance by 10, to shift the decimal point.
	 * Now we can use the normal division operator again.
	 */

	switch (reg) {
	case LTC4245_12VSENSE:
		voltage = regval * 250; /* voltage in uV */
		curr = voltage / 50; /* sense resistor 50 mOhm */
		break;
	case LTC4245_5VSENSE:
		voltage = regval * 125; /* voltage in uV */
		curr = (voltage * 10) / 35; /* sense resistor 3.5 mOhm */
		break;
	case LTC4245_3VSENSE:
		voltage = regval * 125; /* voltage in uV */
		curr = (voltage * 10) / 25; /* sense resistor 2.5 mOhm */
		break;
	case LTC4245_VEESENSE:
		voltage = regval * 250; /* voltage in uV */
		curr = voltage / 100; /* sense resistor 100 mOhm */
		break;
	default:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		curr = 0;
		break;
	}

	return curr;
}