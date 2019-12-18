#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {size_t minor; } ;
struct comedi_cmd {int* chanlist; scalar_t__ start_src; int start_arg; scalar_t__ stop_src; scalar_t__ scan_begin_src; int scan_begin_arg; scalar_t__ convert_src; int convert_arg; } ;
struct TYPE_6__ {scalar_t__ iobase; } ;
struct TYPE_5__ {int i_FirstChannel; int i_LastChannel; scalar_t__ i_Offset; } ;
struct TYPE_4__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_TIMER ; 
 TYPE_3__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 TYPE_2__* s_BoardInfos ; 

int i_APCI3200_CommandAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ui_Configuration = 0;
	/* INT  i_CurrentSource = 0; */
	unsigned int ui_Trigger = 0;
	unsigned int ui_TriggerEdge = 0;
	unsigned int ui_Triggermode = 0;
	unsigned int ui_ScanMode = 0;
	unsigned int ui_ConvertTime = 0;
	unsigned int ui_ConvertTimeBase = 0;
	unsigned int ui_DelayTime = 0;
	unsigned int ui_DelayTimeBase = 0;
	unsigned int ui_DelayMode = 0;
	/* i_FirstChannel=cmd->chanlist[0]; */
	/* i_LastChannel=cmd->chanlist[1]; */
	s_BoardInfos[dev->minor].i_FirstChannel = cmd->chanlist[0];
	s_BoardInfos[dev->minor].i_LastChannel = cmd->chanlist[1];
	if (cmd->start_src == TRIG_EXT) {
		ui_Trigger = 1;
		ui_TriggerEdge = cmd->start_arg & 0xFFFF;
		ui_Triggermode = cmd->start_arg >> 16;
	}			/* if(cmd->start_src==TRIG_EXT) */
	else {
		ui_Trigger = 0;
	}			/* elseif(cmd->start_src==TRIG_EXT) */

	if (cmd->stop_src == TRIG_COUNT) {
		ui_ScanMode = 0;
	}			/*  if (cmd->stop_src==TRIG_COUNT) */
	else {
		ui_ScanMode = 2;
	}			/* else if (cmd->stop_src==TRIG_COUNT) */

	if (cmd->scan_begin_src == TRIG_FOLLOW) {
		ui_DelayTime = 0;
		ui_DelayTimeBase = 0;
		ui_DelayMode = 0;
	}			/* if(cmd->scan_begin_src==TRIG_FOLLOW) */
	else {
		ui_DelayTime = cmd->scan_begin_arg & 0xFFFF;
		ui_DelayTimeBase = cmd->scan_begin_arg >> 16;
		ui_DelayMode = 1;
	}			/* else if(cmd->scan_begin_src==TRIG_FOLLOW) */
	/*         printk("\nui_DelayTime=%u\n",ui_DelayTime); */
	/*         printk("\nui_DelayTimeBase=%u\n",ui_DelayTimeBase); */
	if (cmd->convert_src == TRIG_TIMER) {
		ui_ConvertTime = cmd->convert_arg & 0xFFFF;
		ui_ConvertTimeBase = cmd->convert_arg >> 16;
	} else {
		ui_ConvertTime = 0;
		ui_ConvertTimeBase = 0;
	}

	/*  if(i_ADDIDATAType ==1 || ((i_ADDIDATAType==2))) */
	/*    { */
  /**************************************************/
	/*Read the old configuration of the current source */
  /**************************************************/
	/* ui_Configuration = inl(devpriv->iobase+i_Offset + 12); */
	ui_Configuration =
		inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 12);
  /***********************************************/
	/*Write the configuration of the current source */
  /***********************************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl((ui_Configuration & 0xFFC00000 ), devpriv->iobase+i_Offset +12); */
	outl((ui_Configuration & 0xFFC00000),
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 12);
	/*  } */
	ui_Configuration = 0;
	/*      printk("\nfirstchannel=%u\n",i_FirstChannel); */
	/*      printk("\nlastchannel=%u\n",i_LastChannel); */
	/*      printk("\nui_Trigger=%u\n",ui_Trigger); */
	/*      printk("\nui_TriggerEdge=%u\n",ui_TriggerEdge); */
	/*      printk("\nui_Triggermode=%u\n",ui_Triggermode); */
	/*       printk("\nui_DelayMode=%u\n",ui_DelayMode); */
	/*      printk("\nui_ScanMode=%u\n",ui_ScanMode); */

	/* ui_Configuration = i_FirstChannel |(i_LastChannel << 8)| 0x00100000 | */
	ui_Configuration =
		s_BoardInfos[dev->minor].i_FirstChannel | (s_BoardInfos[dev->
			minor].
		i_LastChannel << 8) | 0x00100000 | (ui_Trigger << 24) |
		(ui_TriggerEdge << 25) | (ui_Triggermode << 27) | (ui_DelayMode
		<< 18) | (ui_ScanMode << 16);

  /*************************/
	/*Write the Configuration */
  /*************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl( ui_Configuration, devpriv->iobase+i_Offset + 0x8); */
	outl(ui_Configuration,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 0x8);
  /***********************/
	/*Write the Delay Value */
  /***********************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(ui_DelayTime,devpriv->iobase+i_Offset + 40); */
	outl(ui_DelayTime,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 40);
  /***************************/
	/*Write the Delay time base */
  /***************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(ui_DelayTimeBase,devpriv->iobase+i_Offset + 44); */
	outl(ui_DelayTimeBase,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 44);
  /*********************************/
	/*Write the conversion time value */
  /*********************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(ui_ConvertTime,devpriv->iobase+i_Offset + 32); */
	outl(ui_ConvertTime,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 32);

  /********************************/
	/*Write the conversion time base */
  /********************************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl(ui_ConvertTimeBase,devpriv->iobase+i_Offset + 36); */
	outl(ui_ConvertTimeBase,
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 36);
  /*******************/
	/*Read the register */
  /*******************/
	/* ui_Configuration = inl(devpriv->iobase+i_Offset + 4); */
	ui_Configuration =
		inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 4);
  /******************/
	/*Set the SCAN bit */
  /******************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;

	/* outl(((ui_Configuration & 0x1E0FF) | 0x00002000),devpriv->iobase+i_Offset + 4); */
	outl(((ui_Configuration & 0x1E0FF) | 0x00002000),
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 4);
  /*******************/
	/*Read the register */
  /*******************/
	ui_Configuration = 0;
	/* ui_Configuration = inl(devpriv->iobase+i_Offset + 8); */
	ui_Configuration =
		inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 8);

  /*******************/
	/*Set the START bit */
  /*******************/
	/* while (((inl(devpriv->iobase+i_Offset+12)>>19) & 1) != 1); */
	while (((inl(devpriv->iobase + s_BoardInfos[dev->minor].i_Offset +
					12) >> 19) & 1) != 1) ;
	/* outl((ui_Configuration | 0x00080000),devpriv->iobase+i_Offset + 8); */
	outl((ui_Configuration | 0x00080000),
		devpriv->iobase + s_BoardInfos[dev->minor].i_Offset + 8);
	return 0;
}