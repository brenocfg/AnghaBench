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
typedef  int /*<<< orphan*/  uint16_t ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS1800_CONTROL_C ; 
 int UB ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  munge_bipolar_sample (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void munge_data(struct comedi_device *dev, uint16_t * array,
		       unsigned int num_elements)
{
	unsigned int i;
	int unipolar;

	/* see if card is using a unipolar or bipolar range so we can munge data correctly */
	unipolar = inb(dev->iobase + DAS1800_CONTROL_C) & UB;

	/* convert to unsigned type if we are in a bipolar mode */
	if (!unipolar) {
		for (i = 0; i < num_elements; i++) {
			array[i] = munge_bipolar_sample(dev, array[i]);
		}
	}
}