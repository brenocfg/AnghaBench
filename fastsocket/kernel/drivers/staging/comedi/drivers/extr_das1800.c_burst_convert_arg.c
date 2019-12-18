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

/* Variables and functions */
#define  TRIG_ROUND_DOWN 130 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 

__attribute__((used)) static unsigned int burst_convert_arg(unsigned int convert_arg, int round_mode)
{
	unsigned int micro_sec;

	/*  in burst mode, the maximum conversion time is 64 microseconds */
	if (convert_arg > 64000)
		convert_arg = 64000;

	/*  the conversion time must be an integral number of microseconds */
	switch (round_mode) {
	case TRIG_ROUND_NEAREST:
	default:
		micro_sec = (convert_arg + 500) / 1000;
		break;
	case TRIG_ROUND_DOWN:
		micro_sec = convert_arg / 1000;
		break;
	case TRIG_ROUND_UP:
		micro_sec = (convert_arg - 1) / 1000 + 1;
		break;
	}

	/*  return number of nanoseconds */
	return micro_sec * 1000;
}