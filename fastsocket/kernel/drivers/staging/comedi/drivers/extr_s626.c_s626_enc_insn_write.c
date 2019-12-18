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
struct enc_private {int /*<<< orphan*/  (* SetLoadTrig ) (struct comedi_device*,struct enc_private*,int) ;int /*<<< orphan*/  (* PulseIndex ) (struct comedi_device*,struct enc_private*) ;} ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG (char*,...) ; 
 int /*<<< orphan*/  Preload (struct comedi_device*,struct enc_private*,unsigned int) ; 
 struct enc_private* encpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,struct enc_private*,int) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,struct enc_private*) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,struct enc_private*,int) ; 

__attribute__((used)) static int s626_enc_insn_write(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{

	struct enc_private *k = &encpriv[CR_CHAN(insn->chanspec)];

	DEBUG("s626_enc_insn_write: encoder write channel %d \n",
	      CR_CHAN(insn->chanspec));

	/*  Set the preload register */
	Preload(dev, k, data[0]);

	/*  Software index pulse forces the preload register to load */
	/*  into the counter */
	k->SetLoadTrig(dev, k, 0);
	k->PulseIndex(dev, k);
	k->SetLoadTrig(dev, k, 2);

	DEBUG("s626_enc_insn_write: End encoder write\n");

	return 1;
}