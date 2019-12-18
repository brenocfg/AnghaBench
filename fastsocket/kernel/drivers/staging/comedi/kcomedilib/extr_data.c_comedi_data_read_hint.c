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
struct comedi_insn {unsigned int* data; unsigned int subdev; int /*<<< orphan*/  chanspec; scalar_t__ n; int /*<<< orphan*/  insn; } ;
typedef  int /*<<< orphan*/  insn ;

/* Variables and functions */
 int /*<<< orphan*/  CR_PACK (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  INSN_READ ; 
 int comedi_do_insn (void*,struct comedi_insn*) ; 
 int /*<<< orphan*/  memset (struct comedi_insn*,int /*<<< orphan*/ ,int) ; 

int comedi_data_read_hint(void *dev, unsigned int subdev,
			  unsigned int chan, unsigned int range,
			  unsigned int aref)
{
	struct comedi_insn insn;
	unsigned int dummy_data;

	memset(&insn, 0, sizeof(insn));
	insn.insn = INSN_READ;
	insn.n = 0;
	insn.data = &dummy_data;
	insn.subdev = subdev;
	insn.chanspec = CR_PACK(chan, range, aref);

	return comedi_do_insn(dev, &insn);
}