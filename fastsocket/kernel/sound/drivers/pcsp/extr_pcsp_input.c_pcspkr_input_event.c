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
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcspkr; int /*<<< orphan*/  timer_active; } ;

/* Variables and functions */
#define  EV_SND 130 
 int PIT_TICK_RATE ; 
#define  SND_BELL 129 
#define  SND_TONE 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__ pcsp_chip ; 
 int /*<<< orphan*/  pcspkr_do_sound (unsigned int) ; 

__attribute__((used)) static int pcspkr_input_event(struct input_dev *dev, unsigned int type,
			      unsigned int code, int value)
{
	unsigned int count = 0;

	if (atomic_read(&pcsp_chip.timer_active) || !pcsp_chip.pcspkr)
		return 0;

	switch (type) {
	case EV_SND:
		switch (code) {
		case SND_BELL:
			if (value)
				value = 1000;
		case SND_TONE:
			break;
		default:
			return -1;
		}
		break;

	default:
		return -1;
	}

	if (value > 20 && value < 32767)
		count = PIT_TICK_RATE / value;

	pcspkr_do_sound(count);

	return 0;
}