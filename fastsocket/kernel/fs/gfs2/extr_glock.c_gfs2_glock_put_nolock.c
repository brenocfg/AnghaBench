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
struct gfs2_glock {int /*<<< orphan*/  gl_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOCK_BUG_ON (struct gfs2_glock*,int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 

void gfs2_glock_put_nolock(struct gfs2_glock *gl)
{
	if (atomic_dec_and_test(&gl->gl_ref))
		GLOCK_BUG_ON(gl, 1);
}