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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct raid_set {TYPE_1__ io; } ;
typedef  enum raid_set_flags { ____Placeholder_raid_set_flags } raid_set_flags ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int RS_DEVEL_STATS ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_reset (struct raid_set*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devel_flags(struct raid_set *rs, int argc, char **argv,
		       enum raid_set_flags flag)
{
	size_t len;

	if (argc != 1)
		return -EINVAL;

	len = strlen(argv[0]);
	if (len < 2)
		len = 2;

	if (!strncmp(argv[0], "on", len))
		return test_and_set_bit(flag, &rs->io.flags) ? -EPERM : 0;
	else if (!strncmp(argv[0], "off", len))
		return test_and_clear_bit(flag, &rs->io.flags) ? 0 : -EPERM;
	else if (!strncmp(argv[0], "reset", len)) {
		if (flag == RS_DEVEL_STATS) {
			if  (test_bit(flag, &rs->io.flags)) {
				stats_reset(rs);
				return 0;
			} else
				return -EPERM;
		} else  {
			set_bit(flag, &rs->io.flags);
			return 0;
		}
	}

	return -EINVAL;
}