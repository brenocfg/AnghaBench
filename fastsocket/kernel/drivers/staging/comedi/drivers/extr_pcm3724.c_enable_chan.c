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
struct priv_pcm3724 {unsigned int dio_1; unsigned int dio_2; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; scalar_t__ private; } ;

/* Variables and functions */
 int CR_CHAN (int) ; 
 int GATE_A0 ; 
 int GATE_A1 ; 
 int GATE_B0 ; 
 int GATE_B1 ; 
 int GATE_C0 ; 
 int GATE_C1 ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void enable_chan(struct comedi_device *dev, struct comedi_subdevice *s,
			int chanspec)
{
	unsigned int mask;
	int gatecfg;
	struct priv_pcm3724 *priv;

	gatecfg = 0;
	priv = (struct priv_pcm3724 *)(dev->private);

	mask = 1 << CR_CHAN(chanspec);
	if (s == dev->subdevices) {	/*  subdev 0 */
		priv->dio_1 |= mask;
	} else {		/* subdev 1 */
		priv->dio_2 |= mask;
	}
	if (priv->dio_1 & 0xff0000) {
		gatecfg |= GATE_C0;
	}
	if (priv->dio_1 & 0xff00) {
		gatecfg |= GATE_B0;
	}
	if (priv->dio_1 & 0xff) {
		gatecfg |= GATE_A0;
	}
	if (priv->dio_2 & 0xff0000) {
		gatecfg |= GATE_C1;
	}
	if (priv->dio_2 & 0xff00) {
		gatecfg |= GATE_B1;
	}
	if (priv->dio_2 & 0xff) {
		gatecfg |= GATE_A1;
	}
	/*       printk("gate control %x\n", gatecfg); */
	outb(gatecfg, dev->iobase + 9);
}