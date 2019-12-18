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
struct gfs2_pcpu_lkstats {int /*<<< orphan*/ * lkstats; } ;
struct TYPE_4__ {unsigned int ln_type; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_stats; TYPE_1__* gl_sbd; int /*<<< orphan*/  gl_dstamp; int /*<<< orphan*/  gl_flags; TYPE_2__ gl_name; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_3__ {int /*<<< orphan*/  sd_lkstats; } ;

/* Variables and functions */
 unsigned int GFS2_LKS_SRTT ; 
 unsigned int GFS2_LKS_SRTTB ; 
 int /*<<< orphan*/  GLF_BLOCKING ; 
 int /*<<< orphan*/  gfs2_update_stats (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct gfs2_pcpu_lkstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gfs2_glock_lock_time (struct gfs2_glock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gfs2_update_reply_times(struct gfs2_glock *gl)
{
	struct gfs2_pcpu_lkstats *lks;
	const unsigned gltype = gl->gl_name.ln_type;
	unsigned index = test_bit(GLF_BLOCKING, &gl->gl_flags) ?
			 GFS2_LKS_SRTTB : GFS2_LKS_SRTT;
	s64 rtt;

	preempt_disable();
	rtt = ktime_to_ns(ktime_sub(ktime_get_real(), gl->gl_dstamp));
	lks = this_cpu_ptr(gl->gl_sbd->sd_lkstats);
	gfs2_update_stats(&gl->gl_stats, index, rtt);		/* Local */
	gfs2_update_stats(&lks->lkstats[gltype], index, rtt);	/* Global */
	preempt_enable();

	trace_gfs2_glock_lock_time(gl, rtt);
}