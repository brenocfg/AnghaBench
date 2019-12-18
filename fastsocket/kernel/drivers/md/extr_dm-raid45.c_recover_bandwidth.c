#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int io_size; int bandwidth_work; scalar_t__ io_count; } ;
struct TYPE_3__ {int io_size; } ;
struct raid_set {scalar_t__ stats; TYPE_2__ recover; TYPE_1__ set; } ;

/* Variables and functions */
 scalar_t__ IO_RECOVER ; 
 scalar_t__ IO_WORK ; 
 scalar_t__ RSBandwidth (struct raid_set*) ; 
 scalar_t__ S_BANDWIDTH ; 
 scalar_t__ S_NO_BANDWIDTH ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int atomic_read (scalar_t__) ; 
 int recover_io_reset (struct raid_set*) ; 

__attribute__((used)) static int recover_bandwidth(struct raid_set *rs)
{
	int r, work;

	/* On reset or when bios delayed -> allow recovery. */
	r = recover_io_reset(rs);
	if (r || RSBandwidth(rs))
		goto out;

	work = atomic_read(rs->recover.io_count + IO_WORK);
	if (work) {
		/* Pay attention to larger recover stripe size. */
		int recover = atomic_read(rs->recover.io_count + IO_RECOVER) *
					  rs->recover.io_size / rs->set.io_size;

		/*
		 * Don't use more than given bandwidth
		 * of the work io for recovery.
		 */
		if (recover > work / rs->recover.bandwidth_work) {
			/* REMOVEME: statistics. */
			atomic_inc(rs->stats + S_NO_BANDWIDTH);
			return 0;
		}
	}

out:
	atomic_inc(rs->stats + S_BANDWIDTH);	/* REMOVEME: statistics. */
	return 1;
}