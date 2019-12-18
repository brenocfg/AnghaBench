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
struct enc_private {int dummy; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG (char*,unsigned int) ; 
 unsigned int ReadLatch (struct comedi_device*,struct enc_private*) ; 
 struct enc_private* encpriv ; 

__attribute__((used)) static int s626_enc_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{

	int n;
	struct enc_private *k = &encpriv[CR_CHAN(insn->chanspec)];

	DEBUG("s626_enc_insn_read: encoder read channel %d \n",
	      CR_CHAN(insn->chanspec));

	for (n = 0; n < insn->n; n++)
		data[n] = ReadLatch(dev, k);

	DEBUG("s626_enc_insn_read: encoder sample %d\n", data[n]);

	return n;
}