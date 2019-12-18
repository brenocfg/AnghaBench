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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_IobaseAmcc; } ;
struct TYPE_3__ {int /*<<< orphan*/  pc_EepromChip; } ;

/* Variables and functions */
 unsigned short CR_CHAN (int /*<<< orphan*/ ) ; 
 TYPE_2__* devpriv ; 
 TYPE_1__* this_board ; 
 unsigned short w_EepromReadWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i_ADDIDATA_InsnReadEeprom(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned short w_Data;
	unsigned short w_Address;
	w_Address = CR_CHAN(insn->chanspec);	/*  address to be read as 0,1,2,3...255 */

	w_Data = w_EepromReadWord(devpriv->i_IobaseAmcc,
		this_board->pc_EepromChip, 0x100 + (2 * w_Address));
	data[0] = w_Data;
	/* multiplied by 2 bcozinput will be like 0,1,2...255 */
	return insn->n;

}