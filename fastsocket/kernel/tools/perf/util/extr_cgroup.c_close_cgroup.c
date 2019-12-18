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
struct cgroup_sel {scalar_t__ refcnt; struct cgroup_sel* name; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cgroup_sel*) ; 

void close_cgroup(struct cgroup_sel *cgrp)
{
	if (!cgrp)
		return;

	/* XXX: not reentrant */
	if (--cgrp->refcnt == 0) {
		close(cgrp->fd);
		free(cgrp->name);
		free(cgrp);
	}
}