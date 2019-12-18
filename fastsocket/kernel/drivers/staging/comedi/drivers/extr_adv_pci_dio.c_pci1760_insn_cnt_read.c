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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CMD_GetIDICntCurValue ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int pci1760_mbxrequest (struct comedi_device*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int pci1760_insn_cnt_read(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	int ret, n;
	unsigned char omb[4] = {
		CR_CHAN(insn->chanspec) & 0x07,
		0x00,
		CMD_GetIDICntCurValue,
		0x00
	};
	unsigned char imb[4];

	for (n = 0; n < insn->n; n++) {
		ret = pci1760_mbxrequest(dev, omb, imb);
		if (!ret)
			return ret;
		data[n] = (imb[1] << 8) + imb[0];
	}

	return n;
}