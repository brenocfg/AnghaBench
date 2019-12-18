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
struct comedi_device {int dummy; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 int CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
#define  MODE_MULT_CHAN_DOWN 130 
#define  MODE_MULT_CHAN_UP 129 
 int MODE_SINGLE_CHAN ; 
#define  MODE_SINGLE_CHAN_INTERVAL 128 
 int /*<<< orphan*/  comedi_error (struct comedi_device const*,char*) ; 
 int labpc_ai_scan_mode (struct comedi_cmd const*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int labpc_ai_chanlist_invalid(const struct comedi_device *dev,
				     const struct comedi_cmd *cmd)
{
	int mode, channel, range, aref, i;

	if (cmd->chanlist == NULL)
		return 0;

	mode = labpc_ai_scan_mode(cmd);

	if (mode == MODE_SINGLE_CHAN)
		return 0;

	if (mode == MODE_SINGLE_CHAN_INTERVAL) {
		if (cmd->chanlist_len > 0xff) {
			comedi_error(dev,
				     "ni_labpc: chanlist too long for single channel interval mode\n");
			return 1;
		}
	}

	channel = CR_CHAN(cmd->chanlist[0]);
	range = CR_RANGE(cmd->chanlist[0]);
	aref = CR_AREF(cmd->chanlist[0]);

	for (i = 0; i < cmd->chanlist_len; i++) {

		switch (mode) {
		case MODE_SINGLE_CHAN_INTERVAL:
			if (CR_CHAN(cmd->chanlist[i]) != channel) {
				comedi_error(dev,
					     "channel scanning order specified in chanlist is not supported by hardware.\n");
				return 1;
			}
			break;
		case MODE_MULT_CHAN_UP:
			if (CR_CHAN(cmd->chanlist[i]) != i) {
				comedi_error(dev,
					     "channel scanning order specified in chanlist is not supported by hardware.\n");
				return 1;
			}
			break;
		case MODE_MULT_CHAN_DOWN:
			if (CR_CHAN(cmd->chanlist[i]) !=
			    cmd->chanlist_len - i - 1) {
				comedi_error(dev,
					     "channel scanning order specified in chanlist is not supported by hardware.\n");
				return 1;
			}
			break;
		default:
			printk("ni_labpc: bug! in chanlist check\n");
			return 1;
			break;
		}

		if (CR_RANGE(cmd->chanlist[i]) != range) {
			comedi_error(dev,
				     "entries in chanlist must all have the same range\n");
			return 1;
		}

		if (CR_AREF(cmd->chanlist[i]) != aref) {
			comedi_error(dev,
				     "entries in chanlist must all have the same reference\n");
			return 1;
		}
	}

	return 0;
}