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
struct seq_file {int dummy; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_spin; } ;

/* Variables and functions */
 int __dump_glock (struct seq_file*,struct gfs2_glock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_glock(struct seq_file *seq, struct gfs2_glock *gl)
{
	int ret;
	spin_lock(&gl->gl_spin);
	ret = __dump_glock(seq, gl);
	spin_unlock(&gl->gl_spin);
	return ret;
}