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
struct TYPE_2__ {int bandwidth; } ;
struct raid_set {TYPE_1__ recover; } ;
typedef  enum raid_set_flags { ____Placeholder_raid_set_flags } raid_set_flags ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_MAX ; 
 int /*<<< orphan*/  BANDWIDTH_MIN ; 
 int EINVAL ; 
 int _absolute (char*,int,int) ; 
 scalar_t__ range_ok (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recover_set_bandwidth (struct raid_set*,int) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static int bandwidth_change(struct raid_set *rs, int argc, char **argv,
			    enum raid_set_flags flag)
{
	int act = rs->recover.bandwidth, bandwidth;

	if (argc != 2)
		return -EINVAL;

	if (sscanf(argv[1], "%d", &bandwidth) == 1 &&
	    range_ok(bandwidth, BANDWIDTH_MIN, BANDWIDTH_MAX)) {
		/* Make delta bandwidth absolute. */
		bandwidth = _absolute(argv[0], act, bandwidth);

		/* Check range. */
		if (range_ok(bandwidth, BANDWIDTH_MIN, BANDWIDTH_MAX)) {
			recover_set_bandwidth(rs, bandwidth);
			return 0;
		}
	}

	return -EINVAL;
}