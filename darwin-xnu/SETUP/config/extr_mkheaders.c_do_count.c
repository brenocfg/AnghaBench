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
struct device {scalar_t__ d_type; scalar_t__ d_slave; scalar_t__ d_flags; int /*<<< orphan*/  d_name; struct device* d_next; } ;

/* Variables and functions */
 scalar_t__ PSEUDO_DEVICE ; 
 scalar_t__ UNKNOWN ; 
 int /*<<< orphan*/  do_header (char const*,char const*,int) ; 
 struct device* dtab ; 
 scalar_t__ eq (int /*<<< orphan*/ ,char const*) ; 

void
do_count(const char *dev, const char *hname, int search)
{
	struct device *dp;
	int count;

	for (count = 0,dp = dtab; dp != 0; dp = dp->d_next)
		if (eq(dp->d_name, dev)) {
			if (dp->d_type == PSEUDO_DEVICE) {
				count =
				    dp->d_slave != UNKNOWN ? dp->d_slave : 1;
				if (dp->d_flags)
					dev = NULL;
				break;
			}
		}
	do_header(dev, hname, count);
}