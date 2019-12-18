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
struct gfs2_sbd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lo_before_commit ) (struct gfs2_sbd*) ;} ;

/* Variables and functions */
 TYPE_1__** gfs2_log_ops ; 
 int /*<<< orphan*/  stub1 (struct gfs2_sbd*) ; 

__attribute__((used)) static inline void lops_before_commit(struct gfs2_sbd *sdp)
{
	int x;
	for (x = 0; gfs2_log_ops[x]; x++)
		if (gfs2_log_ops[x]->lo_before_commit)
			gfs2_log_ops[x]->lo_before_commit(sdp);
}