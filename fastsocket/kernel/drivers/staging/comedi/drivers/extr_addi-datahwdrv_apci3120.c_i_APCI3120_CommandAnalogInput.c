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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {scalar_t__ stop_src; int stop_arg; scalar_t__ start_src; scalar_t__ scan_begin_src; scalar_t__ convert_src; scalar_t__ convert_arg; scalar_t__ scan_begin_arg; int /*<<< orphan*/  chanlist; int /*<<< orphan*/  scan_end_arg; int /*<<< orphan*/  chanlist_len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int ui_AiNbrofScans; int b_AiContinuous; scalar_t__ ui_AiTimer0; scalar_t__ ui_AiTimer1; int /*<<< orphan*/  b_ExttrigEnable; int /*<<< orphan*/  ui_AiDataLength; int /*<<< orphan*/  AiData; int /*<<< orphan*/  pui_AiChannelList; int /*<<< orphan*/  ui_AiScanLength; int /*<<< orphan*/  ui_AiNbrofChannels; int /*<<< orphan*/  ui_AiFlags; } ;
struct TYPE_3__ {int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  prealloc_buf; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  APCI3120_DISABLE ; 
 int /*<<< orphan*/  APCI3120_ENABLE ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_TIMER ; 
 TYPE_2__* devpriv ; 
 int i_APCI3120_CyclicAnalogInput (int,struct comedi_device*,struct comedi_subdevice*) ; 

int i_APCI3120_CommandAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;

	/* loading private structure with cmd structure inputs */
	devpriv->ui_AiFlags = cmd->flags;
	devpriv->ui_AiNbrofChannels = cmd->chanlist_len;
	devpriv->ui_AiScanLength = cmd->scan_end_arg;
	devpriv->pui_AiChannelList = cmd->chanlist;

	/* UPDATE-0.7.57->0.7.68devpriv->AiData=s->async->data; */
	devpriv->AiData = s->async->prealloc_buf;
	/* UPDATE-0.7.57->0.7.68devpriv->ui_AiDataLength=s->async->data_len; */
	devpriv->ui_AiDataLength = s->async->prealloc_bufsz;

	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->ui_AiNbrofScans = cmd->stop_arg;
	} else {
		devpriv->ui_AiNbrofScans = 0;
	}

	devpriv->ui_AiTimer0 = 0;	/*  variables changed to timer0,timer1 */
	devpriv->ui_AiTimer1 = 0;
	if ((devpriv->ui_AiNbrofScans == 0) || (devpriv->ui_AiNbrofScans == -1))
		devpriv->b_AiContinuous = 1;	/*  user want neverending analog acquisition */
	/*  stopped using cancel */

	if (cmd->start_src == TRIG_EXT)
		devpriv->b_ExttrigEnable = APCI3120_ENABLE;
	else
		devpriv->b_ExttrigEnable = APCI3120_DISABLE;

	if (cmd->scan_begin_src == TRIG_FOLLOW) {
		/*  mode 1 or 3 */
		if (cmd->convert_src == TRIG_TIMER) {
			/*  mode 1 */

			devpriv->ui_AiTimer0 = cmd->convert_arg;	/*  timer constant in nano seconds */
			/* return this_board->i_hwdrv_CommandAnalogInput(1,dev,s); */
			return i_APCI3120_CyclicAnalogInput(1, dev, s);
		}

	}
	if ((cmd->scan_begin_src == TRIG_TIMER)
		&& (cmd->convert_src == TRIG_TIMER)) {
		/*  mode 2 */
		devpriv->ui_AiTimer1 = cmd->scan_begin_arg;
		devpriv->ui_AiTimer0 = cmd->convert_arg;	/*  variable changed timer2 to timer0 */
		/* return this_board->i_hwdrv_CommandAnalogInput(2,dev,s); */
		return i_APCI3120_CyclicAnalogInput(2, dev, s);
	}
	return -1;
}