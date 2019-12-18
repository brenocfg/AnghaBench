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
typedef  scalar_t__ u8 ;
struct chan_freq_power {scalar_t__ channel; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct chan_freq_power*) ; 
 struct chan_freq_power* channel_freq_power_UN_BG ; 
 int /*<<< orphan*/  lbs_deb_11d (char*) ; 

__attribute__((used)) static u8 lbs_get_chan_11d(u8 firstchan, u8 nrchan, u8 *chan)
/*find the nrchan-th chan after the firstchan*/
{
	u8 i;
	struct chan_freq_power *cfp;
	u8 cfp_no;

	cfp = channel_freq_power_UN_BG;
	cfp_no = ARRAY_SIZE(channel_freq_power_UN_BG);

	for (i = 0; i < cfp_no; i++) {
		if ((cfp + i)->channel == firstchan) {
			lbs_deb_11d("firstchan found\n");
			break;
		}
	}

	if (i < cfp_no) {
		/*if beyond the boundary */
		if (i + nrchan < cfp_no) {
			*chan = (cfp + i + nrchan)->channel;
			return 1;
		}
	}

	return 0;
}