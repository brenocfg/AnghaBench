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
struct comedi_krange {int max; scalar_t__ min; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ai_range_table; } ;
struct TYPE_3__ {struct comedi_krange* range; } ;

/* Variables and functions */
 TYPE_2__* board (struct comedi_device const*) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device const*,char*) ; 

__attribute__((used)) static unsigned int ai_range_bits_6xxx(const struct comedi_device *dev,
				       unsigned int range_index)
{
	const struct comedi_krange *range =
	    &board(dev)->ai_range_table->range[range_index];
	unsigned int bits = 0;

	switch (range->max) {
	case 10000000:
		bits = 0x000;
		break;
	case 5000000:
		bits = 0x100;
		break;
	case 2000000:
	case 2500000:
		bits = 0x200;
		break;
	case 1000000:
	case 1250000:
		bits = 0x300;
		break;
	case 500000:
		bits = 0x400;
		break;
	case 200000:
	case 250000:
		bits = 0x500;
		break;
	case 100000:
		bits = 0x600;
		break;
	case 50000:
		bits = 0x700;
		break;
	default:
		comedi_error(dev, "bug! in ai_range_bits_6xxx");
		break;
	}
	if (range->min == 0)
		bits += 0x900;
	return bits;
}