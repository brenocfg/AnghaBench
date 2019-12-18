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
struct ubifs_wbuf {scalar_t__ delta; int /*<<< orphan*/  softlimit; int /*<<< orphan*/  timer; int /*<<< orphan*/  jhead; scalar_t__ no_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  dbg_io (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_jhead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

__attribute__((used)) static void new_wbuf_timer_nolock(struct ubifs_wbuf *wbuf)
{
	ubifs_assert(!hrtimer_active(&wbuf->timer));

	if (wbuf->no_timer)
		return;
	dbg_io("set timer for jhead %s, %llu-%llu millisecs",
	       dbg_jhead(wbuf->jhead),
	       div_u64(ktime_to_ns(wbuf->softlimit), USEC_PER_SEC),
	       div_u64(ktime_to_ns(wbuf->softlimit) + wbuf->delta,
		       USEC_PER_SEC));
	hrtimer_start_range_ns(&wbuf->timer, wbuf->softlimit, wbuf->delta,
			       HRTIMER_MODE_REL);
}