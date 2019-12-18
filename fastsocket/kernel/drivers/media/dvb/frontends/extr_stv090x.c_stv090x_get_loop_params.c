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
struct stv090x_state {int srate; int search_range; int search_mode; TYPE_1__* internal; } ;
typedef  int s32 ;
struct TYPE_2__ {int mclk; } ;

/* Variables and functions */
#define  STV090x_SEARCH_AUTO 131 
#define  STV090x_SEARCH_DSS 130 
#define  STV090x_SEARCH_DVBS1 129 
#define  STV090x_SEARCH_DVBS2 128 

__attribute__((used)) static int stv090x_get_loop_params(struct stv090x_state *state, s32 *freq_inc, s32 *timeout_sw, s32 *steps)
{
	s32 timeout, inc, steps_max, srate, car_max;

	srate = state->srate;
	car_max = state->search_range / 1000;
	car_max += car_max / 10;
	car_max  = 65536 * (car_max / 2);
	car_max /= (state->internal->mclk / 1000);

	if (car_max > 0x4000)
		car_max = 0x4000 ; /* maxcarrier should be<= +-1/4 Mclk */

	inc  = srate;
	inc /= state->internal->mclk / 1000;
	inc *= 256;
	inc *= 256;
	inc /= 1000;

	switch (state->search_mode) {
	case STV090x_SEARCH_DVBS1:
	case STV090x_SEARCH_DSS:
		inc *= 3; /* freq step = 3% of srate */
		timeout = 20;
		break;

	case STV090x_SEARCH_DVBS2:
		inc *= 4;
		timeout = 25;
		break;

	case STV090x_SEARCH_AUTO:
	default:
		inc *= 3;
		timeout = 25;
		break;
	}
	inc /= 100;
	if ((inc > car_max) || (inc < 0))
		inc = car_max / 2; /* increment <= 1/8 Mclk */

	timeout *= 27500; /* 27.5 Msps reference */
	if (srate > 0)
		timeout /= (srate / 1000);

	if ((timeout > 100) || (timeout < 0))
		timeout = 100;

	steps_max = (car_max / inc) + 1; /* min steps = 3 */
	if ((steps_max > 100) || (steps_max < 0)) {
		steps_max = 100; /* max steps <= 100 */
		inc = car_max / steps_max;
	}
	*freq_inc = inc;
	*timeout_sw = timeout;
	*steps = steps_max;

	return 0;
}