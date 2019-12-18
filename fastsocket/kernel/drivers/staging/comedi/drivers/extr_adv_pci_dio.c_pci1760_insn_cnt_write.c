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
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int* CntResValue; unsigned char IDICntEnable; } ;

/* Variables and functions */
 unsigned char CMD_EnableIDICounters ; 
 unsigned char CMD_ResetIDICounters ; 
 int /*<<< orphan*/  CMD_SetIDI0CntResetValue ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 
 int pci1760_mbxrequest (struct comedi_device*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int pci1760_insn_cnt_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	int ret;
	unsigned char chan = CR_CHAN(insn->chanspec) & 0x07;
	unsigned char bitmask = 1 << chan;
	unsigned char omb[4] = {
		data[0] & 0xff,
		(data[0] >> 8) & 0xff,
		CMD_SetIDI0CntResetValue + chan,
		0x00
	};
	unsigned char imb[4];

	if (devpriv->CntResValue[chan] != (data[0] & 0xffff)) {	/*  Set reset value if different */
		ret = pci1760_mbxrequest(dev, omb, imb);
		if (!ret)
			return ret;
		devpriv->CntResValue[chan] = data[0] & 0xffff;
	}

	omb[0] = bitmask;	/*  reset counter to it reset value */
	omb[2] = CMD_ResetIDICounters;
	ret = pci1760_mbxrequest(dev, omb, imb);
	if (!ret)
		return ret;

	if (!(bitmask & devpriv->IDICntEnable)) {	/*  start counter if it don't run */
		omb[0] = bitmask;
		omb[2] = CMD_EnableIDICounters;
		ret = pci1760_mbxrequest(dev, omb, imb);
		if (!ret)
			return ret;
		devpriv->IDICntEnable |= bitmask;
	}
	return 1;
}