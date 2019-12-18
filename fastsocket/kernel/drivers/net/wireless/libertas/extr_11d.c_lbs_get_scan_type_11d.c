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
typedef  int /*<<< orphan*/  u8 ;
struct parsed_region_chan_11d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SCAN_TYPE_ACTIVE ; 
 int /*<<< orphan*/  CMD_SCAN_TYPE_PASSIVE ; 
 int /*<<< orphan*/  LBS_DEB_11D ; 
 scalar_t__ lbs_channel_known_11d (int /*<<< orphan*/ ,struct parsed_region_chan_11d*) ; 
 int /*<<< orphan*/  lbs_deb_11d (char*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

u8 lbs_get_scan_type_11d(u8 chan,
			  struct parsed_region_chan_11d * parsed_region_chan)
{
	u8 scan_type = CMD_SCAN_TYPE_PASSIVE;

	lbs_deb_enter(LBS_DEB_11D);

	if (lbs_channel_known_11d(chan, parsed_region_chan)) {
		lbs_deb_11d("found, do active scan\n");
		scan_type = CMD_SCAN_TYPE_ACTIVE;
	} else {
		lbs_deb_11d("not found, do passive scan\n");
	}

	lbs_deb_leave_args(LBS_DEB_11D, "ret scan_type %d", scan_type);
	return scan_type;

}