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
struct comedi_subdevice {int /*<<< orphan*/  async; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int ai_front; int ai_rear; scalar_t__ io_addr; } ;

/* Variables and functions */
 int AI_FIFO_DEPTH ; 
 scalar_t__ DPR_ADC_buffer ; 
 scalar_t__ DPR_AD_Buf_Front ; 
 scalar_t__ DPR_AD_Buf_Rear ; 
 int /*<<< orphan*/  comedi_buf_put (int /*<<< orphan*/ ,short) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 void* readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void dt3k_ai_empty_fifo(struct comedi_device *dev,
			       struct comedi_subdevice *s)
{
	int front;
	int rear;
	int count;
	int i;
	short data;

	front = readw(devpriv->io_addr + DPR_AD_Buf_Front);
	count = front - devpriv->ai_front;
	if (count < 0)
		count += AI_FIFO_DEPTH;

	printk("reading %d samples\n", count);

	rear = devpriv->ai_rear;

	for (i = 0; i < count; i++) {
		data = readw(devpriv->io_addr + DPR_ADC_buffer + rear);
		comedi_buf_put(s->async, data);
		rear++;
		if (rear >= AI_FIFO_DEPTH)
			rear = 0;
	}

	devpriv->ai_rear = rear;
	writew(rear, devpriv->io_addr + DPR_AD_Buf_Rear);
}