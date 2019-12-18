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
struct comedi_subdevice {int type; TYPE_2__* async; } ;
struct TYPE_3__ {int chanlist_len; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;

/* Variables and functions */
#define  COMEDI_SUBD_DI 130 
#define  COMEDI_SUBD_DIO 129 
#define  COMEDI_SUBD_DO 128 
 int bytes_per_sample (struct comedi_subdevice*) ; 

__attribute__((used)) static inline unsigned int cfc_bytes_per_scan(struct comedi_subdevice *subd)
{
	int num_samples;
	int bits_per_sample;

	switch (subd->type) {
	case COMEDI_SUBD_DI:
	case COMEDI_SUBD_DO:
	case COMEDI_SUBD_DIO:
		bits_per_sample = 8 * bytes_per_sample(subd);
		num_samples = (subd->async->cmd.chanlist_len +
			       bits_per_sample - 1) / bits_per_sample;
		break;
	default:
		num_samples = subd->async->cmd.chanlist_len;
		break;
	}
	return num_samples * bytes_per_sample(subd);
}