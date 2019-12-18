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
struct mddev {unsigned long long resync_max; unsigned long long resync_min; scalar_t__ chunk_sectors; int /*<<< orphan*/  recovery; } ;
typedef  size_t ssize_t ;
typedef  unsigned long long sector_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  MD_RECOVERY_RUNNING ; 
 scalar_t__ kstrtoull (char const*,int,unsigned long long*) ; 
 scalar_t__ sector_div (unsigned long long,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
min_sync_store(struct mddev *mddev, const char *buf, size_t len)
{
	unsigned long long min;
	if (kstrtoull(buf, 10, &min))
		return -EINVAL;
	if (min > mddev->resync_max)
		return -EINVAL;
	if (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		return -EBUSY;

	/* Must be a multiple of chunk_size */
	if (mddev->chunk_sectors) {
		sector_t temp = min;
		if (sector_div(temp, mddev->chunk_sectors))
			return -EINVAL;
	}
	mddev->resync_min = min;

	return len;
}