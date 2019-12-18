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
struct r5conf {int /*<<< orphan*/  inactive_list; scalar_t__ quiesce; scalar_t__ inactive_blocked; } ;
struct mddev {struct r5conf* private; } ;

/* Variables and functions */
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 

int md_raid5_congested(struct mddev *mddev, int bits)
{
	struct r5conf *conf = mddev->private;

	/* No difference between reads and writes.  Just check
	 * how busy the stripe_cache is
	 */

	if (conf->inactive_blocked)
		return 1;
	if (conf->quiesce)
		return 1;
	if (list_empty_careful(&conf->inactive_list))
		return 1;

	return 0;
}