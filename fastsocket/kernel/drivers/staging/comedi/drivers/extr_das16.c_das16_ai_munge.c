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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int ai_nbits; } ;

/* Variables and functions */
 short le16_to_cpu (short) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static void das16_ai_munge(struct comedi_device *dev,
			   struct comedi_subdevice *s, void *array,
			   unsigned int num_bytes,
			   unsigned int start_chan_index)
{
	unsigned int i, num_samples = num_bytes / sizeof(short);
	short *data = array;

	for (i = 0; i < num_samples; i++) {
		data[i] = le16_to_cpu(data[i]);
		if (thisboard->ai_nbits == 12) {
			data[i] = (data[i] >> 4) & 0xfff;
		}
	}
}