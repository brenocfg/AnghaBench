#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_9__ {int* dw_MolduleConfiguration; scalar_t__ ui_Address; } ;
struct TYPE_10__ {TYPE_4__ s_BoardInfos; TYPE_3__* s_ModuleInfo; } ;
struct TYPE_7__ {TYPE_1__* s_82X54TimerInfo; } ;
struct TYPE_8__ {TYPE_2__ s_82X54ModuleInfo; } ;
struct TYPE_6__ {int b_82X54Init; unsigned char b_InputClockSelection; unsigned char b_InputClockLevel; unsigned char b_OutputLevel; unsigned char b_HardwareGateLevel; unsigned int dw_ConfigurationWord; } ;

/* Variables and functions */
 unsigned char APCI1710_10MHZ ; 
 int APCI1710_82X54_TIMER ; 
 unsigned char APCI1710_FRONT_CONNECTOR_INPUT ; 
 unsigned char APCI1710_PCI_BUS_CLOCK ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_5__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

int i_APCI1710_InsnConfigInitTimer(struct comedi_device *dev, struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{

	int i_ReturnValue = 0;
	unsigned char b_ModulNbr;
	unsigned char b_TimerNbr;
	unsigned char b_TimerMode;
	unsigned int ul_ReloadValue;
	unsigned char b_InputClockSelection;
	unsigned char b_InputClockLevel;
	unsigned char b_OutputLevel;
	unsigned char b_HardwareGateLevel;

	/* BEGIN JK 27.10.2003 : Add the possibility to use a 40 Mhz quartz */
	unsigned int dw_Test = 0;
	/* END JK 27.10.2003 : Add the possibility to use a 40 Mhz quartz */

	i_ReturnValue = insn->n;
	b_ModulNbr = (unsigned char) CR_AREF(insn->chanspec);
	b_TimerNbr = (unsigned char) CR_CHAN(insn->chanspec);
	b_TimerMode = (unsigned char) data[0];
	ul_ReloadValue = (unsigned int) data[1];
	b_InputClockSelection = (unsigned char) data[2];
	b_InputClockLevel = (unsigned char) data[3];
	b_OutputLevel = (unsigned char) data[4];
	b_HardwareGateLevel = (unsigned char) data[5];

	/* Test the module number */
	if (b_ModulNbr < 4) {
		/* Test if 82X54 timer */
		if ((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0xFFFF0000UL) == APCI1710_82X54_TIMER) {
			/* Test the timer number */

			if (b_TimerNbr <= 2) {
				/* Test the timer mode */
				if (b_TimerMode <= 5) {
					/* BEGIN JK 27.10.2003 : Add the possibility to use a 40 Mhz quartz */
					/* Test te imput clock selection */
					/*
					   if (((b_TimerNbr == 0) && (b_InputClockSelection == 0)) ||
					   ((b_TimerNbr != 0) && ((b_InputClockSelection == 0) || (b_InputClockSelection == 1))))
					 */

					if (((b_TimerNbr == 0) &&
					     (b_InputClockSelection == APCI1710_PCI_BUS_CLOCK)) ||
					    ((b_TimerNbr == 0) &&
					     (b_InputClockSelection == APCI1710_10MHZ)) ||
					    ((b_TimerNbr != 0) &&
					     ((b_InputClockSelection == APCI1710_PCI_BUS_CLOCK) ||
					      (b_InputClockSelection == APCI1710_FRONT_CONNECTOR_INPUT) ||
					      (b_InputClockSelection == APCI1710_10MHZ)))) {
						/* BEGIN JK 27.10.2003 : Add the possibility to use a 40 Mhz quartz */
						if (((b_InputClockSelection == APCI1710_10MHZ) &&
						     ((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0x0000FFFFUL) >= 0x3131)) ||
						     (b_InputClockSelection != APCI1710_10MHZ)) {
							/* END JK 27.10.2003 : Add the possibility to use a 40 Mhz quartz */
							/* Test the input clock level selection */

							if ((b_InputClockLevel == 0) ||
							    (b_InputClockLevel == 1)) {
								/* Test the output clock level selection */
								if ((b_OutputLevel == 0) || (b_OutputLevel == 1)) {
									/* Test the hardware gate level selection */
									if ((b_HardwareGateLevel == 0) || (b_HardwareGateLevel == 1)) {
										/* BEGIN JK 27.10.03 : Add the possibility to use a 40 Mhz quartz */
										/* Test if version > 1.1 and clock selection = 10MHz */
										if ((b_InputClockSelection == APCI1710_10MHZ) && ((devpriv->s_BoardInfos.dw_MolduleConfiguration[b_ModulNbr] & 0x0000FFFFUL) > 0x3131)) {
											/* Test if 40MHz quartz on board */
											dw_Test = inl(devpriv->s_BoardInfos.ui_Address + (16 + (b_TimerNbr * 4) + (64 * b_ModulNbr)));

											dw_Test = (dw_Test >> 16) & 1;
										} else {
											dw_Test = 1;
										}

										/* Test if detection OK */
										if (dw_Test == 1) {
											/* END JK 27.10.03 : Add the possibility to use a 40 Mhz quartz */
											/* Initialisation OK */
											devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_82X54Init = 1;

											/* Save the input clock selection */
											devpriv-> s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_InputClockSelection = b_InputClockSelection;

											/* Save the input clock level */
											devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_InputClockLevel = ~b_InputClockLevel & 1;

											/* Save the output level */
											devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_OutputLevel = ~b_OutputLevel & 1;

											/* Save the gate level */
											devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].b_HardwareGateLevel = b_HardwareGateLevel;

											/* Set the configuration word and disable the timer */
											/* BEGIN JK 27.10.03 : Add the possibility to use a 40 Mhz quartz */
											/*
											   devpriv->s_ModuleInfo [b_ModulNbr].
											   s_82X54ModuleInfo.
											   s_82X54TimerInfo  [b_TimerNbr].
											   dw_ConfigurationWord = (unsigned int) (((b_HardwareGateLevel         << 0) & 0x1) |
											   ((b_InputClockLevel           << 1) & 0x2) |
											   (((~b_OutputLevel       & 1)  << 2) & 0x4) |
											   ((b_InputClockSelection       << 4) & 0x10));
											 */
											/* Test if 10MHz selected */
											if (b_InputClockSelection == APCI1710_10MHZ) {
												b_InputClockSelection = 2;
											}

											devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].dw_ConfigurationWord = (unsigned int)(((b_HardwareGateLevel << 0) & 0x1) | ((b_InputClockLevel << 1) & 0x2) | (((~b_OutputLevel & 1) << 2) & 0x4) | ((b_InputClockSelection << 4) & 0x30));
											/* END JK 27.10.03 : Add the possibility to use a 40 Mhz quartz */
											outl(devpriv->s_ModuleInfo[b_ModulNbr].s_82X54ModuleInfo.s_82X54TimerInfo[b_TimerNbr].dw_ConfigurationWord, devpriv->s_BoardInfos.ui_Address + 32 + (b_TimerNbr * 4) + (64 * b_ModulNbr));

											/* Initialise the 82X54 Timer */
											outl((unsigned int) b_TimerMode, devpriv->s_BoardInfos.ui_Address + 16 + (b_TimerNbr * 4) + (64 * b_ModulNbr));

											/* Write the reload value */
											outl(ul_ReloadValue, devpriv->s_BoardInfos.ui_Address + 0 + (b_TimerNbr * 4) + (64 * b_ModulNbr));
											/* BEGIN JK 27.10.03 : Add the possibility to use a 40 Mhz quartz */
										}	/*  if (dw_Test == 1) */
										else {
											/* Input timer clock selection is wrong */
											i_ReturnValue = -6;
										}	/*  if (dw_Test == 1) */
										/* END JK 27.10.03 : Add the possibility to use a 40 Mhz quartz */
									}	/*  if ((b_HardwareGateLevel == 0) || (b_HardwareGateLevel == 1)) */
									else {
										/* Selection from hardware gate level is wrong */
										DPRINTK("Selection from hardware gate level is wrong\n");
										i_ReturnValue = -9;
									}	/*  if ((b_HardwareGateLevel == 0) || (b_HardwareGateLevel == 1)) */
								}	/*  if ((b_OutputLevel == 0) || (b_OutputLevel == 1)) */
								else {
									/* Selection from output clock level is wrong */
									DPRINTK("Selection from output clock level is wrong\n");
									i_ReturnValue = -8;
								}	/*  if ((b_OutputLevel == 0) || (b_OutputLevel == 1)) */
							}	/*  if ((b_InputClockLevel == 0) || (b_InputClockLevel == 1)) */
							else {
								/* Selection from input clock level is wrong */
								DPRINTK("Selection from input clock level is wrong\n");
								i_ReturnValue = -7;
							}	/*  if ((b_InputClockLevel == 0) || (b_InputClockLevel == 1)) */
						} else {
							/* Input timer clock selection is wrong */
							DPRINTK("Input timer clock selection is wrong\n");
							i_ReturnValue = -6;
						}
					} else {
						/* Input timer clock selection is wrong */
						DPRINTK("Input timer clock selection is wrong\n");
						i_ReturnValue = -6;
					}
				}	/*  if ((b_TimerMode >= 0) && (b_TimerMode <= 5)) */
				else {
					/* Timer mode selection is wrong */
					DPRINTK("Timer mode selection is wrong\n");
					i_ReturnValue = -5;
				}	/*  if ((b_TimerMode >= 0) && (b_TimerMode <= 5)) */
			}	/*  if ((b_TimerNbr >= 0) && (b_TimerNbr <= 2)) */
			else {
				/* Timer selection wrong */
				DPRINTK("Timer selection wrong\n");
				i_ReturnValue = -3;
			}	/*  if ((b_TimerNbr >= 0) && (b_TimerNbr <= 2)) */
		} else {
			/* The module is not a TIMER module */
			DPRINTK("The module is not a TIMER module\n");
			i_ReturnValue = -4;
		}
	} else {
		/* Module number error */
		DPRINTK("Module number error\n");
		i_ReturnValue = -2;
	}

	return i_ReturnValue;
}