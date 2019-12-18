#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {size_t minor; } ;
struct TYPE_4__ {int i_ConnectionType; size_t i_ADDIDATAGain; TYPE_1__* s_Module; } ;
struct TYPE_3__ {unsigned int ul_CurrentSourceCJC; unsigned int* ul_CurrentSource; unsigned int* ul_GainFactor; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,unsigned int) ; 
 TYPE_2__* s_BoardInfos ; 

int i_APCI3200_GetChannelCalibrationValue(struct comedi_device *dev,
	unsigned int ui_Channel_num, unsigned int *CJCCurrentSource,
	unsigned int *ChannelCurrentSource, unsigned int *ChannelGainFactor)
{
	int i_DiffChannel = 0;
	int i_Module = 0;

#ifdef PRINT_INFO
	printk("\n Channel = %u", ui_Channel_num);
#endif

	/* Test if single or differential mode */
	if (s_BoardInfos[dev->minor].i_ConnectionType == 1) {
		/* if diff */

		if ((ui_Channel_num >= 0) && (ui_Channel_num <= 1))
			i_DiffChannel = ui_Channel_num, i_Module = 0;
		else if ((ui_Channel_num >= 2) && (ui_Channel_num <= 3))
			i_DiffChannel = ui_Channel_num - 2, i_Module = 1;
		else if ((ui_Channel_num >= 4) && (ui_Channel_num <= 5))
			i_DiffChannel = ui_Channel_num - 4, i_Module = 2;
		else if ((ui_Channel_num >= 6) && (ui_Channel_num <= 7))
			i_DiffChannel = ui_Channel_num - 6, i_Module = 3;

	} else {
		/*  if single */
		if ((ui_Channel_num == 0) || (ui_Channel_num == 1))
			i_DiffChannel = 0, i_Module = 0;
		else if ((ui_Channel_num == 2) || (ui_Channel_num == 3))
			i_DiffChannel = 1, i_Module = 0;
		else if ((ui_Channel_num == 4) || (ui_Channel_num == 5))
			i_DiffChannel = 0, i_Module = 1;
		else if ((ui_Channel_num == 6) || (ui_Channel_num == 7))
			i_DiffChannel = 1, i_Module = 1;
		else if ((ui_Channel_num == 8) || (ui_Channel_num == 9))
			i_DiffChannel = 0, i_Module = 2;
		else if ((ui_Channel_num == 10) || (ui_Channel_num == 11))
			i_DiffChannel = 1, i_Module = 2;
		else if ((ui_Channel_num == 12) || (ui_Channel_num == 13))
			i_DiffChannel = 0, i_Module = 3;
		else if ((ui_Channel_num == 14) || (ui_Channel_num == 15))
			i_DiffChannel = 1, i_Module = 3;
	}

	/* Test if thermocouple or RTD mode */
	*CJCCurrentSource =
		s_BoardInfos[dev->minor].s_Module[i_Module].ul_CurrentSourceCJC;
#ifdef PRINT_INFO
	printk("\n CJCCurrentSource = %lu", *CJCCurrentSource);
#endif

	*ChannelCurrentSource =
		s_BoardInfos[dev->minor].s_Module[i_Module].
		ul_CurrentSource[i_DiffChannel];
#ifdef PRINT_INFO
	printk("\n ChannelCurrentSource = %lu", *ChannelCurrentSource);
#endif
	/*       } */
	/*    } */

	/* Channle gain factor */
	*ChannelGainFactor =
		s_BoardInfos[dev->minor].s_Module[i_Module].
		ul_GainFactor[s_BoardInfos[dev->minor].i_ADDIDATAGain];
#ifdef PRINT_INFO
	printk("\n ChannelGainFactor = %lu", *ChannelGainFactor);
#endif
	/* End JK 21.10.2004: APCI-3200 / APCI-3300 Reading of EEPROM values */

	return 0;
}