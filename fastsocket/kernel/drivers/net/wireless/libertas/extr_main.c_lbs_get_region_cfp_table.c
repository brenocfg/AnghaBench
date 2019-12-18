#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct chan_freq_power {int dummy; } ;
struct TYPE_3__ {scalar_t__ region; int cfp_no_BG; struct chan_freq_power* cfp_BG; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lbs_deb_main (char*,scalar_t__) ; 
 TYPE_1__* region_cfp_table ; 

struct chan_freq_power *lbs_get_region_cfp_table(u8 region, int *cfp_no)
{
	int i, end;

	lbs_deb_enter(LBS_DEB_MAIN);

	end = ARRAY_SIZE(region_cfp_table);

	for (i = 0; i < end ; i++) {
		lbs_deb_main("region_cfp_table[i].region=%d\n",
			region_cfp_table[i].region);
		if (region_cfp_table[i].region == region) {
			*cfp_no = region_cfp_table[i].cfp_no_BG;
			lbs_deb_leave(LBS_DEB_MAIN);
			return region_cfp_table[i].cfp_BG;
		}
	}

	lbs_deb_leave_args(LBS_DEB_MAIN, "ret NULL");
	return NULL;
}