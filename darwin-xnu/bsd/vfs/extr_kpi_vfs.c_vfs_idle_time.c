#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  TYPE_2__* mount_t ;
struct TYPE_4__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {TYPE_1__ mnt_last_write_completed_timestamp; scalar_t__ mnt_pending_write_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  microuptime (struct timeval*) ; 

uint64_t vfs_idle_time(mount_t mp)
{
	if (mp->mnt_pending_write_size)
		return 0;

	struct timeval now;

	microuptime(&now);

	return ((now.tv_sec
			 - mp->mnt_last_write_completed_timestamp.tv_sec) * 1000000
			+ now.tv_usec - mp->mnt_last_write_completed_timestamp.tv_usec);
}