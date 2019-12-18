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
struct TYPE_2__ {unsigned long last_jiffies; scalar_t__ io_count; } ;
struct raid_set {TYPE_1__ recover; } ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ IO_RECOVER ; 
 scalar_t__ IO_WORK ; 
 int /*<<< orphan*/  atomic_set (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 

__attribute__((used)) static int recover_io_reset(struct raid_set *rs)
{
	unsigned long j = jiffies;

	/* Pay attention to jiffies overflows. */
	if (j > rs->recover.last_jiffies + HZ ||
	    j < rs->recover.last_jiffies) {
		atomic_set(rs->recover.io_count + IO_WORK, 0);
		atomic_set(rs->recover.io_count + IO_RECOVER, 0);
		rs->recover.last_jiffies = j;
		return 1;
	}

	return 0;
}