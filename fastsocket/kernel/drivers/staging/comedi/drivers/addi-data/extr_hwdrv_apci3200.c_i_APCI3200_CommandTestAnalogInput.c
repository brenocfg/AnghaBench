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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {size_t minor; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; int start_arg; int* chanlist; int convert_arg; int scan_begin_arg; } ;
struct TYPE_2__ {scalar_t__ i_InterruptFlag; int i_FirstChannel; int i_LastChannel; } ;

/* Variables and functions */
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int /*<<< orphan*/  fpu_begin () ; 
 int /*<<< orphan*/  fpu_end () ; 
 int /*<<< orphan*/  i_APCI3200_Reset (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* s_BoardInfos ; 

int i_APCI3200_CommandTestAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_cmd *cmd)
{

	int err = 0;
	int tmp;		/*  divisor1,divisor2; */
	unsigned int ui_ConvertTime = 0;
	unsigned int ui_ConvertTimeBase = 0;
	unsigned int ui_DelayTime = 0;
	unsigned int ui_DelayTimeBase = 0;
	int i_Triggermode = 0;
	int i_TriggerEdge = 0;
	int i_NbrOfChannel = 0;
	int i_Cpt = 0;
	double d_ConversionTimeForAllChannels = 0.0;
	double d_SCANTimeNewUnit = 0.0;
	/*  step 1: make sure trigger sources are trivially valid */

	tmp = cmd->start_src;
	cmd->start_src &= TRIG_NOW | TRIG_EXT;
	if (!cmd->start_src || tmp != cmd->start_src)
		err++;
	tmp = cmd->scan_begin_src;
	cmd->scan_begin_src &= TRIG_TIMER | TRIG_FOLLOW;
	if (!cmd->scan_begin_src || tmp != cmd->scan_begin_src)
		err++;
	tmp = cmd->convert_src;
	cmd->convert_src &= TRIG_TIMER;
	if (!cmd->convert_src || tmp != cmd->convert_src)
		err++;
	tmp = cmd->scan_end_src;
	cmd->scan_end_src &= TRIG_COUNT;
	if (!cmd->scan_end_src || tmp != cmd->scan_end_src)
		err++;
	tmp = cmd->stop_src;
	cmd->stop_src &= TRIG_COUNT | TRIG_NONE;
	if (!cmd->stop_src || tmp != cmd->stop_src)
		err++;
	/* if(i_InterruptFlag==0) */
	if (s_BoardInfos[dev->minor].i_InterruptFlag == 0) {
		err++;
		/*           printk("\nThe interrupt should be enabled\n"); */
	}
	if (err) {
		i_APCI3200_Reset(dev);
		return 1;
	}

	if (cmd->start_src != TRIG_NOW && cmd->start_src != TRIG_EXT) {
		err++;
	}
	if (cmd->start_src == TRIG_EXT) {
		i_TriggerEdge = cmd->start_arg & 0xFFFF;
		i_Triggermode = cmd->start_arg >> 16;
		if (i_TriggerEdge < 1 || i_TriggerEdge > 3) {
			err++;
			printk("\nThe trigger edge selection is in error\n");
		}
		if (i_Triggermode != 2) {
			err++;
			printk("\nThe trigger mode selection is in error\n");
		}
	}

	if (cmd->scan_begin_src != TRIG_TIMER &&
		cmd->scan_begin_src != TRIG_FOLLOW)
		err++;

	if (cmd->convert_src != TRIG_TIMER)
		err++;

	if (cmd->scan_end_src != TRIG_COUNT) {
		cmd->scan_end_src = TRIG_COUNT;
		err++;
	}

	if (cmd->stop_src != TRIG_NONE && cmd->stop_src != TRIG_COUNT)
		err++;

	if (err) {
		i_APCI3200_Reset(dev);
		return 2;
	}
	/* i_FirstChannel=cmd->chanlist[0]; */
	s_BoardInfos[dev->minor].i_FirstChannel = cmd->chanlist[0];
	/* i_LastChannel=cmd->chanlist[1]; */
	s_BoardInfos[dev->minor].i_LastChannel = cmd->chanlist[1];

	if (cmd->convert_src == TRIG_TIMER) {
		ui_ConvertTime = cmd->convert_arg & 0xFFFF;
		ui_ConvertTimeBase = cmd->convert_arg >> 16;
		if (ui_ConvertTime != 20 && ui_ConvertTime != 40
			&& ui_ConvertTime != 80 && ui_ConvertTime != 160)
		{
			printk("\nThe selection of conversion time reload value is in error\n");
			err++;
		}		/*  if (ui_ConvertTime!=20 && ui_ConvertTime!=40 && ui_ConvertTime!=80 && ui_ConvertTime!=160 ) */
		if (ui_ConvertTimeBase != 2) {
			printk("\nThe selection of conversion time unit  is in error\n");
			err++;
		}		/* if(ui_ConvertTimeBase!=2) */
	} else {
		ui_ConvertTime = 0;
		ui_ConvertTimeBase = 0;
	}
	if (cmd->scan_begin_src == TRIG_FOLLOW) {
		ui_DelayTime = 0;
		ui_DelayTimeBase = 0;
	}			/* if(cmd->scan_begin_src==TRIG_FOLLOW) */
	else {
		ui_DelayTime = cmd->scan_begin_arg & 0xFFFF;
		ui_DelayTimeBase = cmd->scan_begin_arg >> 16;
		if (ui_DelayTimeBase != 2 && ui_DelayTimeBase != 3) {
			err++;
			printk("\nThe Delay time base selection is in error\n");
		}
		if (ui_DelayTime < 1 || ui_DelayTime > 1023) {
			err++;
			printk("\nThe Delay time value is in error\n");
		}
		if (err) {
			i_APCI3200_Reset(dev);
			return 3;
		}
		fpu_begin();
		d_SCANTimeNewUnit = (double)ui_DelayTime;
		/* i_NbrOfChannel= i_LastChannel-i_FirstChannel + 4; */
		i_NbrOfChannel =
			s_BoardInfos[dev->minor].i_LastChannel -
			s_BoardInfos[dev->minor].i_FirstChannel + 4;
      /**********************************************************/
		/*calculate the total conversion time for all the channels */
      /**********************************************************/
		d_ConversionTimeForAllChannels =
			(double)((double)ui_ConvertTime /
			(double)i_NbrOfChannel);

      /*******************************/
		/*Convert the frequence in time */
      /*******************************/
		d_ConversionTimeForAllChannels =
			(double)1.0 / d_ConversionTimeForAllChannels;
		ui_ConvertTimeBase = 3;
      /***********************************/
		/*Test if the time unit is the same */
      /***********************************/

		if (ui_DelayTimeBase <= ui_ConvertTimeBase) {

			for (i_Cpt = 0;
				i_Cpt < (ui_ConvertTimeBase - ui_DelayTimeBase);
				i_Cpt++) {

				d_ConversionTimeForAllChannels =
					d_ConversionTimeForAllChannels * 1000;
				d_ConversionTimeForAllChannels =
					d_ConversionTimeForAllChannels + 1;
			}
		} else {
			for (i_Cpt = 0;
				i_Cpt < (ui_DelayTimeBase - ui_ConvertTimeBase);
				i_Cpt++) {
				d_SCANTimeNewUnit = d_SCANTimeNewUnit * 1000;

			}
		}

		if (d_ConversionTimeForAllChannels >= d_SCANTimeNewUnit) {

			printk("\nSCAN Delay value cannot be used\n");
	  /*********************************/
			/*SCAN Delay value cannot be used */
	  /*********************************/
			err++;
		}
		fpu_end();
	}			/* else if(cmd->scan_begin_src==TRIG_FOLLOW) */

	if (err) {
		i_APCI3200_Reset(dev);
		return 4;
	}

	return 0;
}