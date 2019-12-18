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
struct comedi_insn {int n; unsigned int* data; unsigned int subdev; int /*<<< orphan*/  chanspec; int /*<<< orphan*/  insn; } ;
typedef  int /*<<< orphan*/  insn ;

/* Variables and functions */
 int /*<<< orphan*/  CR_PACK (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  INSN_WRITE ; 
 int comedi_do_insn (void*,struct comedi_insn*) ; 
 int /*<<< orphan*/  memset (struct comedi_insn*,int /*<<< orphan*/ ,int) ; 

int comedi_data_write(void *dev, unsigned int subdev, unsigned int chan,
		      unsigned int range, unsigned int aref, unsigned int data)
{
	struct comedi_insn insn;

	memset(&insn, 0, sizeof(insn));
	insn.insn = INSN_WRITE;
	insn.n = 1;
	insn.data = &data;
	insn.subdev = subdev;
	insn.chanspec = CR_PACK(chan, range, aref);

	return comedi_do_insn(dev, &insn);
}