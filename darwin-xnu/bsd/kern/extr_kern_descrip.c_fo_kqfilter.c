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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct knote {int dummy; } ;
struct kevent_internal_s {int dummy; } ;
struct fileproc {TYPE_1__* f_ops; } ;
struct TYPE_2__ {int (* fo_kqfilter ) (struct fileproc*,struct knote*,struct kevent_internal_s*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct fileproc*,struct knote*,struct kevent_internal_s*,int /*<<< orphan*/ ) ; 

int
fo_kqfilter(struct fileproc *fp, struct knote *kn,
		struct kevent_internal_s *kev, vfs_context_t ctx)
{
        return ((*fp->f_ops->fo_kqfilter)(fp, kn, kev, ctx));
}