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
struct gfs2_tune {int /*<<< orphan*/  gt_spin; } ;
struct gfs2_sbd {struct gfs2_tune sd_tune; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t tune_set(struct gfs2_sbd *sdp, unsigned int *field,
			int check_zero, const char *buf, size_t len)
{
	struct gfs2_tune *gt = &sdp->sd_tune;
	unsigned int x;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	x = simple_strtoul(buf, NULL, 0);

	if (check_zero && !x)
		return -EINVAL;

	spin_lock(&gt->gt_spin);
	*field = x;
	spin_unlock(&gt->gt_spin);
	return len;
}