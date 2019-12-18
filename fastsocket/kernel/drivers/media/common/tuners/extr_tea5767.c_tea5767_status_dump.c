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
struct TYPE_2__ {int xtal_freq; } ;
struct tea5767_priv {TYPE_1__ ctrl; } ;

/* Variables and functions */
 unsigned char TEA5767_ADC_LEVEL_MASK ; 
 unsigned char TEA5767_BAND_LIMIT_MASK ; 
 unsigned char TEA5767_CHIP_ID_MASK ; 
#define  TEA5767_HIGH_LO_13MHz 131 
#define  TEA5767_HIGH_LO_32768 130 
 unsigned char TEA5767_IF_CNTR_MASK ; 
#define  TEA5767_LOW_LO_13MHz 129 
#define  TEA5767_LOW_LO_32768 128 
 unsigned char TEA5767_READY_FLAG_MASK ; 
 unsigned char TEA5767_RESERVED_MASK ; 
 unsigned char TEA5767_STEREO_MASK ; 
 int /*<<< orphan*/  tuner_info (char*,...) ; 

__attribute__((used)) static void tea5767_status_dump(struct tea5767_priv *priv,
				unsigned char *buffer)
{
	unsigned int div, frq;

	if (TEA5767_READY_FLAG_MASK & buffer[0])
		tuner_info("Ready Flag ON\n");
	else
		tuner_info("Ready Flag OFF\n");

	if (TEA5767_BAND_LIMIT_MASK & buffer[0])
		tuner_info("Tuner at band limit\n");
	else
		tuner_info("Tuner not at band limit\n");

	div = ((buffer[0] & 0x3f) << 8) | buffer[1];

	switch (priv->ctrl.xtal_freq) {
	case TEA5767_HIGH_LO_13MHz:
		frq = (div * 50000 - 700000 - 225000) / 4;	/* Freq in KHz */
		break;
	case TEA5767_LOW_LO_13MHz:
		frq = (div * 50000 + 700000 + 225000) / 4;	/* Freq in KHz */
		break;
	case TEA5767_LOW_LO_32768:
		frq = (div * 32768 + 700000 + 225000) / 4;	/* Freq in KHz */
		break;
	case TEA5767_HIGH_LO_32768:
	default:
		frq = (div * 32768 - 700000 - 225000) / 4;	/* Freq in KHz */
		break;
	}
	buffer[0] = (div >> 8) & 0x3f;
	buffer[1] = div & 0xff;

	tuner_info("Frequency %d.%03d KHz (divider = 0x%04x)\n",
		   frq / 1000, frq % 1000, div);

	if (TEA5767_STEREO_MASK & buffer[2])
		tuner_info("Stereo\n");
	else
		tuner_info("Mono\n");

	tuner_info("IF Counter = %d\n", buffer[2] & TEA5767_IF_CNTR_MASK);

	tuner_info("ADC Level = %d\n",
		   (buffer[3] & TEA5767_ADC_LEVEL_MASK) >> 4);

	tuner_info("Chip ID = %d\n", (buffer[3] & TEA5767_CHIP_ID_MASK));

	tuner_info("Reserved = 0x%02x\n",
		   (buffer[4] & TEA5767_RESERVED_MASK));
}