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
struct gfs2_glock {int /*<<< orphan*/  gl_stats; TYPE_1__* gl_sbd; int /*<<< orphan*/  gl_dstamp; TYPE_2__ gl_name; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  sd_lkstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_LKS_SIRT ; 
 int /*<<< orphan*/  gfs2_update_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct gfs2_pcpu_lkstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gfs2_update_request_times(struct gfs2_glock *gl)
{
	struct gfs2_pcpu_lkstats *lks;
	const unsigned gltype = gl->gl_name.ln_type;
	ktime_t dstamp;
	s64 irt;

	preempt_disable();
	dstamp = gl->gl_dstamp;
	gl->gl_dstamp = ktime_get_real();
	irt = ktime_to_ns(ktime_sub(gl->gl_dstamp, dstamp));
	lks = this_cpu_ptr(gl->gl_sbd->sd_lkstats);
	gfs2_update_stats(&gl->gl_stats, GFS2_LKS_SIRT, irt);		/* Local */
	gfs2_update_stats(&lks->lkstats[gltype], GFS2_LKS_SIRT, irt);	/* Global */
	preempt_enable();
}