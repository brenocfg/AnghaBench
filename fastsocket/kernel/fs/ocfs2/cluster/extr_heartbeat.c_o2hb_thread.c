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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct o2hb_region {unsigned int hr_timeout_ms; int hr_blocks; int /*<<< orphan*/ * hr_slots; int /*<<< orphan*/  hr_unclean_stop; } ;
struct o2hb_bio_wait_ctxt {int dummy; } ;

/* Variables and functions */
 int ML_HEARTBEAT ; 
 int ML_KTHREAD ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mlog (int,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  msleep_interruptible (unsigned int) ; 
 int /*<<< orphan*/  o2hb_disarm_write_timeout (struct o2hb_region*) ; 
 int o2hb_do_disk_heartbeat (struct o2hb_region*) ; 
 unsigned int o2hb_elapsed_msecs (struct timeval*,struct timeval*) ; 
 int o2hb_issue_node_write (struct o2hb_region*,struct o2hb_bio_wait_ctxt*) ; 
 int /*<<< orphan*/  o2hb_prepare_block (struct o2hb_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2hb_shutdown_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2hb_wait_on_io (struct o2hb_region*,struct o2hb_bio_wait_ctxt*) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int o2hb_thread(void *data)
{
	int i, ret;
	struct o2hb_region *reg = data;
	struct o2hb_bio_wait_ctxt write_wc;
	struct timeval before_hb, after_hb;
	unsigned int elapsed_msec;

	mlog(ML_HEARTBEAT|ML_KTHREAD, "hb thread running\n");

	set_user_nice(current, -20);

	while (!kthread_should_stop() && !reg->hr_unclean_stop) {
		/* We track the time spent inside
		 * o2hb_do_disk_heartbeat so that we avoid more than
		 * hr_timeout_ms between disk writes. On busy systems
		 * this should result in a heartbeat which is less
		 * likely to time itself out. */
		do_gettimeofday(&before_hb);

		i = 0;
		do {
			ret = o2hb_do_disk_heartbeat(reg);
		} while (ret && ++i < 2);

		do_gettimeofday(&after_hb);
		elapsed_msec = o2hb_elapsed_msecs(&before_hb, &after_hb);

		mlog(0, "start = %lu.%lu, end = %lu.%lu, msec = %u\n",
		     before_hb.tv_sec, (unsigned long) before_hb.tv_usec,
		     after_hb.tv_sec, (unsigned long) after_hb.tv_usec,
		     elapsed_msec);

		if (elapsed_msec < reg->hr_timeout_ms) {
			/* the kthread api has blocked signals for us so no
			 * need to record the return value. */
			msleep_interruptible(reg->hr_timeout_ms - elapsed_msec);
		}
	}

	o2hb_disarm_write_timeout(reg);

	/* unclean stop is only used in very bad situation */
	for(i = 0; !reg->hr_unclean_stop && i < reg->hr_blocks; i++)
		o2hb_shutdown_slot(&reg->hr_slots[i]);

	/* Explicit down notification - avoid forcing the other nodes
	 * to timeout on this region when we could just as easily
	 * write a clear generation - thus indicating to them that
	 * this node has left this region.
	 *
	 * XXX: Should we skip this on unclean_stop? */
	o2hb_prepare_block(reg, 0);
	ret = o2hb_issue_node_write(reg, &write_wc);
	if (ret == 0) {
		o2hb_wait_on_io(reg, &write_wc);
	} else {
		mlog_errno(ret);
	}

	mlog(ML_HEARTBEAT|ML_KTHREAD, "hb thread exiting\n");

	return 0;
}