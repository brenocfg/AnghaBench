#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gfs2_sbd {int /*<<< orphan*/  sd_lkstats; } ;
struct TYPE_5__ {size_t ln_type; } ;
struct gfs2_glock {TYPE_2__ gl_name; struct gfs2_sbd* gl_sbd; } ;
struct TYPE_6__ {TYPE_1__* lkstats; } ;
struct TYPE_4__ {int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 TYPE_3__* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gfs2_sbstats_inc(const struct gfs2_glock *gl, int which)
{
	const struct gfs2_sbd *sdp = gl->gl_sbd;
	preempt_disable();
	this_cpu_ptr(sdp->sd_lkstats)->lkstats[gl->gl_name.ln_type].stats[which]++;
	preempt_enable();
}